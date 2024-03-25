/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_populateAttributes.cpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:20 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/25 19:33:25 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Initiliazing constant key maps ******************************************* */

map<string, void (Server::*)(const vector<string>&)> populateServerKeys( void ) {
	map<string, void (Server::*)(const vector<string>&)> keys;
	
	keys["listen"] = &Server::setListen;
	keys["host"] = &Server::setHost;
	keys["server_name"] = &Server::setServerName;
	keys["error_page"] = &Server::setErrorPage;
	keys["client_max_body_size"] = &Server::setClientMaxBodySize;
	keys["client_body_in_file_only"] = &Server::setClientBodyInFileOnly;
	keys["client_body_buffer_size"] = &Server::setClientBodyBufferSize;
	keys["client_body_timeout"] = &Server::setClientBodyTimeOut;
	keys["location"] = &Server::addLocation;

	return (keys);
}

map<string, void (StdLocation::*)(const vector<string>&)> populateStdLocationKeys( void ) {
	map<string, void (StdLocation::*)(const vector<string>&)> keys;

	keys["location"] = &ALocation::setPath;
	keys["allow"] = &ALocation::setAllow;
	keys["autoindex"] = &ALocation::setAutoIndex;
	keys["index"] = &StdLocation::setIndex;

	return (keys);
}

map<string, void (Upload::*)(const vector<string>&)> populateUploadKeys( void ) {
	map<string, void (Upload::*)(const vector<string>&)>	keys;
	
	keys["location"] = &ALocation::setPath;
	keys["allow"] = &ALocation::setAllow;
	keys["autoindex"] = &ALocation::setAutoIndex;
	keys["allow"] = &Upload::setAllow;
	keys["upload_store"] = &Upload::setUploadStore;

	return (keys);
}

map<string, void (Cgi::*)(const vector<string>&)>	populateCgiKeys( void ) {
	map<string, void (Cgi::*)(const vector<string>&)> keys;

	keys["location"] = &ALocation::setPath;

	return (keys);
};

const map<string, void (Server::*)(const vector<string>&)>		Parser::_serverKeys = populateServerKeys();
const map<string, void (StdLocation::*)(const vector<string>&)>	Parser::_stdLocationKeys = populateStdLocationKeys();
const map<string, void (Upload::*)(const vector<string>&)> 		Parser::_uploadKeys = populateUploadKeys();
const map<string, void (Cgi::*)(const vector<string>&)>			Parser::_CgiKeys = populateCgiKeys();

/* Initializing new server ************************************************** */

void	Parser::initServerBlock( Configuration& config, vector<string>& tokens ) {
	if (!isValidServerLine(tokens)) {
		stringstream ss;
		ss << "Invalid server config at line " << tokens.at(0) << ", expected format is \"server {\"" << endl;
		throw (invalid_argument(ss.str()));
	}
	config.addServer();
}

/* Populating attributes **************************************************** */

void	Parser::populateServerAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (Server::*)(const vector<string>&)>::const_iterator cit = _serverKeys.find(tokens.at(1));

	if (cit != _serverKeys.end()) {
		Server&	current_server = config.getServer("LAST");
		try {
			(current_server.*(cit->second))(tokens);
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for a server block";
		throw (invalid_argument(ss.str()));
	}
}

void	Parser::populateStdLocationAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (StdLocation::*)(const vector<string>&)>::const_iterator cit = _stdLocationKeys.find(tokens.at(1));

	if (cit != _stdLocationKeys.end()) {
		Server&			current_server = config.getServer("LAST");
		ALocation*		current_location = current_server.getLocation("LAST");
		StdLocation*	std_location = dynamic_cast<StdLocation*>(current_location);

		if (current_location && std_location) {
			try {
				(std_location->*(cit->second))(tokens);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		else {
			stringstream ss; 
			ss << "Invalid or non-existent location: " << tokens.at(2);
			throw (logic_error(ss.str()));
		}
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for a standard location block";
		throw (invalid_argument(ss.str()));
	}
}

void	Parser::populateUploadAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (Upload::*)(const vector<string>&)>::const_iterator cit = _uploadKeys.find(tokens.at(1));

	if (cit != _uploadKeys.end()) {
		Server&			current_server = config.getServer("LAST");
		ALocation*		current_location = current_server.getLocation("LAST");
		Upload*			upload_location = dynamic_cast<Upload*>(current_location);

		if (current_location && upload_location) {
			try {
				(upload_location->*(cit->second))(tokens);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		else {
			stringstream ss; 
			ss << "Invalid or non-existent location: " << tokens.at(2);
			throw (logic_error(ss.str()));
		}
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for an upload location block";
		throw (invalid_argument(ss.str()));
	}
}

void	Parser::populateCgiAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (Cgi::*)(const vector<string>&)>::const_iterator cit = _CgiKeys.find(tokens.at(1));

	if (cit != _CgiKeys.end()) {
		Server&		current_server = config.getServer("LAST");
		ALocation*	current_location = current_server.getLocation("LAST");
		Cgi*		cgi_location = dynamic_cast<Cgi*>(current_location);

		if (current_location && cgi_location) {
			try {
				(cgi_location->*(cit->second))(tokens);
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << std::endl;
			}
		}
		else {
			stringstream ss; 
			ss << "Invalid or non-existent location: " << tokens.at(2);
			throw (logic_error(ss.str()));
		}
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for a CGI location block";
		throw (invalid_argument(ss.str()));
	}
}
