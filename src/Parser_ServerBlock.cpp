/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_ServerBlock.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:20 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/19 10:10:11 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

bool	Parser::isValidServerLine( vector<string>& tokens ) {
	if (tokens.size() != 3 || tokens.at(2) != "{")
		return (false);
	else
		return (true);
}

void	Parser::initServerBlock( Configuration& config, vector<string>& tokens, blockType** curr_block ) {
	if (!isValidServerLine(tokens)) {
		stringstream ss;
		ss << "Invalid server config at line " << tokens.at(0) << ", expected format is \"server {\"" << endl;
		throw (invalid_argument(ss.str()));
	}
	config.addServer();
	**curr_block = SERVER;
}

void	Parser::populateServerAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (Server::*)(const vector<string>&)>::const_iterator cit = _serverKeys.find(tokens.at(1));

	if (cit != _serverKeys.end()) {
		Server&	current_server = config.getServer("LAST");
		(current_server.*(cit->second))(tokens);
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for a server block";
		throw (ss.str());
	}
}

void	Parser::populateStdLocationAttribute( Configuration& config, const vector<string>& tokens ) {
	map<string, void (StdLocation::*)(const vector<string>&)>::const_iterator cit = _stdLocationKeys.find(tokens.at(1));

	if (cit != _stdLocationKeys.end()) {
		Server&			current_server = config.getServer("LAST");
		ALocation*		current_location = current_server.getLocation("LAST");
		StdLocation*	std_location = dynamic_cast<StdLocation*>(current_location);

		if (current_location && std_location) {
			(std_location->*(cit->second))(tokens);
		}
		else {
			stringstream ss; 
			ss << "Invalid or non-existent location";
			throw (logic_error(ss.str()));
		}
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": invalid \"" << tokens.at(1) << "\" key for a standard location block";
		throw (ss.str());
	}
}
