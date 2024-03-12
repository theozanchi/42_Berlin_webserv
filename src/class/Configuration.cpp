/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:39:49 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"
#include "Server.hpp"

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
