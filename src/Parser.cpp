/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/14 18:54:04 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Private attributes ******************************************************* */

map<string, void (Server::*)(const vector<string>&)>	populateKeys( void ) {
	map<string, void (Server::*)(const vector<string>&)>	keys;
	
	keys["server"] = NULL;
	keys["listen"] = &Server::setListen;
	keys["host"] = &Server::setHost;
	keys["server_name"] = &Server::setServerName;
	keys["error_page"] = &Server::setErrorPage;
	keys["client_max_body_size"] = &Server::setClientMaxBodySize;
	keys["client_body_in_file_only"] = &Server::setClientMaxBodySize;
	keys["client_body_buffer_size"] = &Server::setClientBodyBufferSize;
	keys["client_body_timeout"] = &Server::setClientBodyTimeOut;
	keys["location"] = NULL;
	keys["allow"] = NULL;
	keys["index"] = NULL;
	keys["autoindex"] = NULL;
	keys["upload_store"] = NULL;

	return (keys);
}

set<string>	populateStdLocationKeys( void ) {
	set<string>	keys;
	
	keys.insert("allow");
	keys.insert("index");
	keys.insert("autoindex");

	return (keys);
}

set<string>	populateUploadKeys( void ) {
	set<string>	keys;
	
	keys.insert("allow");
	keys.insert("upload_store");

	return (keys);
}

set<string>	populateCGIKeys( void ) {
	set<string>	keys;

	keys.insert("tbd");

	return (keys);
};

const map<string, void (Server::*)(const vector<string>&)>	Parser::_keys = populateKeys();
const set<string>	Parser::_authorizedStdLocationKeys = populateStdLocationKeys();
const set<string>	Parser::_authorizedUploadKeys = populateUploadKeys();
const set<string>	Parser::_authorizedCGIKeys = populateCGIKeys();

/* Private methods ********************************************************** */

bool	Parser::checkCurlyBrackets( ifstream& ifs ) {
	int		opening_brackets = 0;
	int		closing_brackets = 0;
	string	line;

	while (getline(ifs, line)) {
		opening_brackets += count(line.begin(), line.end(), '{');
		closing_brackets += count(line.begin(), line.end(), '}');
	}

	ifs.clear();			//clearing any potential error flag
	ifs.seekg(0, ios::beg);	//setting back offset to begin of ifs

	return (opening_brackets == closing_brackets);
}

bool	Parser::isEmpty( const string& line ) {
	if (line.empty())
		return (true);
	
	for (string::const_iterator it = line.begin(); it < line.end(); ++it) {
		if (!isspace(*it) && *it != '}' && *it != '{')
			return (false);
	}
	
	return (true);
}

bool	Parser::isCommented( const string& line ) {
	string::const_iterator	it = line.begin();

	while (isspace(*it))
		++it;

	if (*it == '#')
		return (true);
	else
		return (false);
}

vector<string>	Parser::extractTokens( const string& line, size_t line_count ) {
	vector<string>	tokens;
	ostringstream	oss;
	istringstream	iss(line);
	string			token;

	oss << line_count;
	tokens.push_back(oss.str());

	while (iss >> token) {
		tokens.push_back(token);
	}

	return (tokens);
}

void	Parser::checkForWrongSemiColon( vector<string>* tokens ) {
	for (vector<string>::iterator it = tokens->begin() + 1; it < tokens->end(); ++it) {
		size_t semicolon = (*it).find(';');

		if (semicolon != string::npos) {
			if (semicolon != (*it).length() - 1) {
				stringstream ss;
				ss << "Invalid config at line " << tokens->at(0) << ": semi-colon not at the end-of-line";
				throw (invalid_argument(ss.str()));
			}
		}
	}
}

void	Parser::checkAndTrimSemiColon( vector<string>* tokens ) {
	vector<string>::reverse_iterator rit = tokens->rbegin();
	
	if (tokens->at(1) == "server" || tokens->at(1) == "location")
		return ;
	checkForWrongSemiColon(tokens);
	if (*rit == ";") {
		tokens->erase(next(rit).base());	//Converting the reverse iterator into a forward one
	}
	else if ((*rit).back() == ';') {
		*rit = (*rit).substr(0, (*rit).length() - 1);
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens->at(0) << ": missing semi-colon at end-of-line";
		throw (invalid_argument(ss.str())); 
	}
}

void	Parser::parseLine( Configuration& config, const string& line, size_t line_count, blockType* curr_block ) {
	if (isEmpty(line) || isCommented(line))
		return ;

	vector<string>	tokens = extractTokens(line, line_count);

	if (_keys.find(tokens.at(1)) == _keys.end()) {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": \"" << tokens.at(1) << "\" not supported";
		throw (invalid_argument(ss.str()));
	}
	if (tokens.at(1) == "server")
		initServerBlock(config, tokens, &curr_block);
	else
		checkAndTrimSemiColon(&tokens);
	for (vector<string>::iterator it = tokens.begin(); it < tokens.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

/* Public methods *********************************************************** */

void	Parser::parseFile( Configuration& config, const char* file ) {
	ifstream	ifs;
	string		line;
	size_t		line_count = 1;
	blockType	block_type;

	ifs.open(file, ifstream::in);
	if (!checkCurlyBrackets(ifs))
		throw (invalid_argument("Incorrect number of brackets {} in " + string(file)));
	while (getline(ifs, line)) {
		parseLine(config, line, line_count, &block_type);
		line_count++;
	}
	(void)config;
	ifs.close();
}
