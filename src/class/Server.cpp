/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/19 10:27:20 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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

Server::~Server() {
	for (map<string, ALocation*>::iterator it = _location.begin(); it != _location.end(); ++it) {
		delete it->second;
		_location.erase(it->first);
	}
}

/* Setters ****************************************************************** */

void	Server::setListen( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 1; it < tokens.end(); ++it) {
		_listen.push_back(stoi(*it));
	}
}

void	Server::setHost( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 1; it < tokens.end(); ++it) {
		_host.push_back(*it);
	}
}

void	Server::setServerName( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 1; it < tokens.end(); ++it) {
		_serverName.push_back(*it);
	}
}

void	Server::setErrorPage( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 1; it < tokens.end() - 1; ++it) {
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

void	Server::addLocation( const vector<string>& tokens ) {
	if (tokens.at(1).front() == '~')
		_location[tokens.at(1)] = new Cgi();
	else if (tokens.at(1).find("upload") != string::npos)
		_location[tokens.at(1)] = new Upload();
	else
		_location[tokens.at(1)] = new StdLocation();
	
	_location[tokens.at(1)]->setPath(tokens);
}

ALocation*	Server::getLocation( const string& path_or_flag ) {
	if (_location.find(path_or_flag) != _location.end()) {
		return (_location[path_or_flag]);
	}
	else if (path_or_flag == "LAST") {
		map<string, ALocation*>::reverse_iterator rit = _location.rbegin();
		return (rit->second);
	}
	else {
		throw (invalid_argument("Invalid argument for getLocation()"));
	}
}
