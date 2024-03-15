/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 12:30:59 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

Configuration::Configuration() {}

Configuration::Configuration( const Configuration& src )
	:	_server( src._server )
	{}

Configuration& Configuration::operator=( const Configuration& src ) {
	if (this != &src) {
		_server = src._server;
	}
	return (*this);
}

Configuration::~Configuration() {}

/* Member functions ********************************************************* */

void	Configuration::addServer( void ) {
	_server.push_back(Server());
}

Server&	Configuration::getServer( size_t idx ) {
	if (idx < _server.size()) {
		return (_server[idx]);
	}
	else {
		throw (invalid_argument("Invalid index for getServer()"));
	}		
}

Server&	Configuration::getServer( const string& flag ) {
	if (flag == "LAST") {
		return (_server.back());
	}
	else {
		throw (invalid_argument("Invalid flag for getServer()"));
	}
}
