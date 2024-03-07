/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:52:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 17:11:31 by tzanchi          ###   ########.fr       */
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

/* Static methods *********************************************************** */

void	Parser::printAuthorizedKeys( void ) {
	for (set<string>::iterator it = _authorizedKeys.begin(); it != _authorizedKeys.end(); ++it) {
		cout << *it << endl;
	}
}
