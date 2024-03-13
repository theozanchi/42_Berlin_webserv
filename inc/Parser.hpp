/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/13 11:26:31 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <set>
# include <string>
# include <fstream>
# include <exception>
# include <algorithm>
# include <sstream>

using namespace std;

class Configuration;

enum blockType {
	NO_BLOCK,
	SERVER,
	STD_LOCATION,
	UPLOAD,
	CGI
};

class Parser {
private:
	Parser() {}
	~Parser() {}

	static const set<string>	_authorizedKeys;
	static const set<string>	_authorizedStdLocationKeys;
	static const set<string>	_authorizedUploadKeys;
	static const set<string>	_authorizedCGIKeys;

	static bool	checkCurlyBrackets( ifstream& ifs );

	static bool	isEmpty( const string& line );
	static bool	isCommented( const string& line );	

	static vector<string>	extractTokens( const string& line, size_t line_count );

	static bool	isValidServerLine( vector<string>& tokens );
	static void	initServerBlock(Configuration& config, vector<string>& tokens, blockType** curr_block );

	static void	parseLine( Configuration& config, const string& line, size_t line_count, blockType* curr_block );

public:

	static void	parseFile( Configuration& config, const char* file );
};

#endif
