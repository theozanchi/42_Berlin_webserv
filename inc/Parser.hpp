/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/11 12:48:38 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <set>
# include <string>
# include <fstream>
# include <exception>
# include <algorithm>

using namespace std;

class Configuration;

class Parser {
private:
	Parser() {}
	~Parser() {}

	static const set<string>	_authorizedKeys;
	static const set<string>	_authorizedStdLocationKeys;
	static const set<string>	_authorizedUploadKeys;
	static const set<string>	_authorizedCGIKeys;

	static bool	checkCurlyBrackets( ifstream& ifs );
	static void	parseLine( Configuration* config, const string& line );

public:

	static void	parseFile( Configuration* config, const char* file );
};

#endif
