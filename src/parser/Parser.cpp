/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 09:08:07 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Private methods ********************************************************** */

void	Parser::updateCurrBlockFlag( const vector<string>& tokens, blockType** curr_block ) {
	if (tokens.at(1) == "server") {
		**curr_block = SERVER;
	}
	else if (tokens.at(1) == "location") {
		if (tokens.at(2).at(0) == '~')
			**curr_block = CGI;
		else if (tokens.at(2).find("upload") != string::npos)
			**curr_block = UPLOAD;
		else
			**curr_block = STD_LOCATION;
	}
	else if (tokens.at(1) == "}") {
		if (**curr_block >= STD_LOCATION)
			**curr_block = SERVER;
		else
			**curr_block = NO_BLOCK;
	}
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

	if (tokens.at(1) == "server") {
		initServerBlock(config, tokens);
		updateCurrBlockFlag(tokens, &curr_block);
		return;
	}
	else if (tokens.at(1) == "}") {
		updateCurrBlockFlag(tokens, &curr_block);
		return;
	}
	else {
		checkAndTrimSemiColon(&tokens);
	}

	switch (*curr_block) {
		case SERVER:
			populateServerAttribute(config, tokens);
			break;
		case STD_LOCATION:
			populateStdLocationAttribute(config, tokens);
			break;
		case UPLOAD:
			populateUploadAttribute(config, tokens);
			break;
		case CGI:
			populateCgiAttribute(config, tokens);
			break;
		default:
			break;
	}
	updateCurrBlockFlag(tokens, &curr_block);
}

/* Public methods *********************************************************** */

void	Parser::parseFile( Configuration& config, const char* file ) {
	ifstream	ifs;
	string		line;
	size_t		line_count = 1;
	blockType	block_type = NO_BLOCK;

	ifs.open(file, ifstream::in);
	if (!checkCurlyBrackets(ifs))
		throw (invalid_argument("Incorrect number of brackets {} in " + string(file)));
	while (getline(ifs, line)) {
		parseLine(config, line, line_count, &block_type);
		line_count++;
	}
	ifs.close();
}
