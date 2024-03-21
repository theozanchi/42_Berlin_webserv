/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 09:12:04 by tzanchi          ###   ########.fr       */
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
class Server;

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
	
	// Key maps
	static const map<string, void (Server::*)(const vector<string>&)>		_serverKeys;
	static const map<string, void (StdLocation::*)(const vector<string>&)>	_stdLocationKeys;
	static const map<string, void (Upload::*)(const vector<string>&)>		_uploadKeys;
	static const map<string, void (Cgi::*)(const vector<string>&)>			_CgiKeys;

	// Populate attributes
	static void	initServerBlock( Configuration& config, vector<string>& tokens );
	static void	populateServerAttribute( Configuration& config, const vector<string>& tokens );
	static void	populateStdLocationAttribute( Configuration& config, const vector<string>& tokens );
	static void	populateUploadAttribute( Configuration& config, const vector<string>& tokens );
	static void	populateCgiAttribute( Configuration& config, const vector<string>& tokens );

	// Utils
	static bool	checkCurlyBrackets( ifstream& ifs );
	static bool	isEmpty( const string& line );
	static bool	isCommented( const string& line );	
	static bool	isValidServerLine( vector<string>& tokens );
	static void	checkForWrongSemiColon( vector<string>* tokens );
	static void	checkAndTrimSemiColon( vector<string>* tokens );

	// Main parsing functions
	static void				updateCurrBlockFlag( const vector<string>& tokens, blockType** curr_block );
	static vector<string>	extractTokens( const string& line, size_t line_count );
	static void				parseLine( Configuration& config, const string& line, size_t line_count, blockType* curr_block );

public:
	static void	parseFile( Configuration& config, const char* file );
};

#endif
