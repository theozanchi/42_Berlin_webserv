/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:32:26 by tzanchi          ###   ########.fr       */
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

	static string	extractKey( const string& line, size_t line_count );

	static bool	isValidServerLine( const string& line );
	static void	initServerBlock(Configuration& config, const string& line, size_t line_count );

	static void	parseLine( Configuration& config, const string& line, size_t line_count, blockType* block_type );

public:

	static void	parseFile( Configuration& config, const char* file );
};

#endif
