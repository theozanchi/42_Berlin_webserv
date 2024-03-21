/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:04:14 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 09:07:40 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
		if (!isspace(*it) && *it != '{')
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

bool	Parser::isValidServerLine( vector<string>& tokens ) {
	if (tokens.size() != 3 || tokens.at(2) != "{")
		return (false);
	else
		return (true);
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
		tokens->erase(rit.base());	//Converting the reverse iterator into a forward one
	}
	else if ((*rit).at((*rit).length() - 1) == ';') {
		*rit = (*rit).substr(0, (*rit).length() - 1);
	}
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens->at(0) << ": missing semi-colon at end-of-line";
		throw (invalid_argument(ss.str())); 
	}
}