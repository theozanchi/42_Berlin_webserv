/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 15:59:27 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Private attributes ******************************************************* */

const set<string>	Parser::_authorizedKeys = {
	"listen",
	"host",
	"server_name",
	"error_page",
	"client_max_body_size",
	"client_body_in_file_only",
	"client_body_buffer_size",
	"client_body_timeout",
	"location",
	"allow",
	"index",
	"autoindex",
	"upload_store"
};

/* Static methods *********************************************************** */

void	Parser::printAuthorizedKeys( void ) {
	for (set<string>::iterator it = _authorizedKeys.begin(); it != _authorizedKeys.end(); ++it) {
		cout << *it << endl;
	}
}
