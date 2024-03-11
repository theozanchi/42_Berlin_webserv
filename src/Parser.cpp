/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/11 12:50:45 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Private attributes ******************************************************* */

set<string>	populateAuthorizedKeys( void ) {
	set<string>	keys;
	
	keys.insert("listen");
	keys.insert("host");
	keys.insert("server_name");
	keys.insert("error_page");
	keys.insert("client_max_body_size");
	keys.insert("client_body_in_file_only");
	keys.insert("client_body_buffer_size");
	keys.insert("client_body_timeout");
	keys.insert("location");

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

void	Parser::parseLine( Configuration* config, const string& line ) {
	(void)config;
	(void)line;
}

/* Public methods *********************************************************** */

void	Parser::parseFile( Configuration* config, const char* file ) {
	ifstream	ifs;
	string		line;

	ifs.open(file, ifstream::in);
	if (!checkCurlyBrackets(ifs))
		throw (invalid_argument("Incorrect number of brackets {} in " + string(file)));
	// while (getline(ifs, line)) {
	// 	parseLine(config, line);
	// }
	(void)config;
	ifs.close();
}
