/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/14 11:59:45 by tzanchi          ###   ########.fr       */
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

/* Setters ****************************************************************** */

void	Server::setListen( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin(); it < tokens.end(); ++it) {
		_listen.push_back(stoi(*it));
	}
}

void	Server::setHost( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin(); it < tokens.end(); ++it) {
		_host.push_back(*it);
	}
}

void	Server::setServerName( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin(); it < tokens.end(); ++it) {
		_serverName.push_back(*it);
	}
}

void	Server::setErrorPage( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin(); it < tokens.end() - 1; ++it) {
		_errorPage.insert(make_pair(stoi(*it), tokens.back()));
	}
}

void	Server::setClientMaxBodySize( const vector<string>& tokens ) { 
	_clientMaxBodySize = stoi(tokens.at(1));
}

void	Server::setClientBodyInFileOnly( const vector<string>& tokens ) {
	tokens.at(1) == "on" ? _clientBodyInFileOnly = true : _clientBodyInFileOnly = false ;
}

void	Server::setClientBodyBufferSize( const vector<string>& tokens ) {
	_clientBodyBufferSize = stoi(tokens.at(1));
}

void	Server::setClientBodyTimeOut( const vector<string>& tokens ) {
	_clientBodyTimeOut = stoi(tokens.at(1));
}
