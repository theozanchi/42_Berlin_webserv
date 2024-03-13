/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser_ServerBlock.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:18:20 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/13 11:57:20 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

bool	Parser::isValidServerLine( vector<string>& tokens ) {
	if (tokens.size() != 3 || tokens.at(2) != "{")
		return (false);
	else
		return (true);
}

void	Parser::initServerBlock( Configuration& config, vector<string>& tokens, blockType** curr_block ) {
	if (!isValidServerLine(tokens)) {
		stringstream ss;
		ss << "Invalid server config at line " << tokens.at(0) << ", expected format is \"server {\"" << endl;
		throw (invalid_argument(ss.str()));
	}
	config.addServer();
	**curr_block = SERVER;
}

