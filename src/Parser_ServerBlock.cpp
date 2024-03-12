/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_ServerBlock.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:20 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:33:05 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

bool	Parser::isValidServerLine( const string& line ) {
	size_t i = line.find("server") + 6;

	while (line[i] && isspace(line[i]))
		++i;
	if (line[i] != '{')
		return (false);
	++i;
	while (line[i]) {
		if (!isspace(line[i]))
			return (false);
		++i;
	}
	return (true);
}

void	Parser::initServerBlock( Configuration& config, const string& line, size_t line_count ) {
	if (!isValidServerLine(line)) {
		stringstream ss;
		ss << "Invalid server config at line " << line_count << ": " << line << endl;
		ss << "Expected line format is \"server {\"";
		throw (invalid_argument(ss.str()));
	}
	cout << "test1" << endl;
	config.addServer();
	cout << "test2" << endl;
}

