/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:40:36 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ALocation.hpp"
#include "StdLocation.hpp"
#include "Upload.hpp"
#include "CGI.hpp"

/* Constructors, assignment operator and destructor ************************* */

Server::Server() {}

Server::Server( const Server& src )
	:	_listen(src._listen),
		_host(src._host),
		_serverName(src._serverName),
		_errorPage(src._errorPage),
		_clientMaxBodySize(src._clientMaxBodySize),
		_clientBodyInFileOnly(src._clientBodyInFileOnly),
		_clientBodyBufferSize(src._clientBodyBufferSize),
		_clientBodyTimeOut(src._clientBodyTimeOut),
		_location(src._location)
	{}

Server& Server::operator=( const Server& src ) {
	if (this != &src) {
		_listen = src._listen;
		_host = src._host;
		_serverName = src._serverName;
		_errorPage = src._errorPage;
		_clientMaxBodySize = src._clientMaxBodySize;
		_clientBodyInFileOnly = src._clientBodyInFileOnly;
		_clientBodyBufferSize = src._clientBodyBufferSize;
		_clientBodyTimeOut = src._clientBodyTimeOut;
		_location = src._location;
	}
	return (*this);
}

Server::~Server() {}

/* Member functions ********************************************************* */
