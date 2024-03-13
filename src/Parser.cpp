/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/13 11:57:54 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Private attributes ******************************************************* */

set<string>	populateAuthorizedKeys( void ) {
	set<string>	keys;
	
	keys.insert("server");
	keys.insert("listen");
	keys.insert("host");
	keys.insert("server_name");
	keys.insert("error_page");
	keys.insert("client_max_body_size");
	keys.insert("client_body_in_file_only");
	keys.insert("client_body_buffer_size");
	keys.insert("client_body_timeout");
	keys.insert("location");
	keys.insert("allow");
	keys.insert("index");
	keys.insert("autoindex");
	keys.insert("upload_store");

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

const set<string>	Parser::_authorizedKeys = populateAuthorizedKeys();
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

void	Parser::parseLine( Configuration& config, const string& line, size_t line_count, blockType* curr_block ) {
	if (isEmpty(line) || isCommented(line))
		return ;

	vector<string>	tokens = extractTokens(line, line_count);

	if (_authorizedKeys.find(tokens.at(1)) == _authorizedKeys.end()) {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": \"" << tokens.at(1) << "\" not supported";
		throw (invalid_argument(ss.str()));
	}
	if (tokens.at(1) == "server")
		initServerBlock(config, tokens, &curr_block);
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
