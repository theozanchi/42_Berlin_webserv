/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/22 10:30:53 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

Server::Server()
	:	_clientBodyInFileOnly(false),
		_isListenSet(false),
		_isHostSet(false),
		_isServerNameSet(false),
		_isErrorPageSet(false),
		_isClientMaxBodySizeSet(false),
		_isClientBodyInFileOnlySet(false),
		_isClientBodyBufferSizeSet(false),
		_isClientBodyTimeOutSet(false) {}

Server::Server( const Server& src )
	:	_listen(src._listen),
		_host(src._host),
		_serverName(src._serverName),
		_errorPage(src._errorPage),
		_clientMaxBodySize(src._clientMaxBodySize),
		_clientBodyInFileOnly(src._clientBodyInFileOnly),
		_clientBodyBufferSize(src._clientBodyBufferSize),
		_clientBodyTimeOut(src._clientBodyTimeOut),
		_isListenSet(src._isListenSet),
		_isHostSet(src._isHostSet),
		_isServerNameSet(src._isServerNameSet),
		_isErrorPageSet(src._isErrorPageSet),
		_isClientMaxBodySizeSet(src._isClientMaxBodySizeSet),
		_isClientBodyInFileOnlySet(src._isClientBodyInFileOnlySet),
		_isClientBodyBufferSizeSet(src._isClientBodyBufferSizeSet),
		_isClientBodyTimeOutSet(src._isClientBodyTimeOutSet) {
	for (map<string, ALocation*>::const_iterator cit = src._location.begin(); cit != src._location.end(); ++cit) {
			_location[cit->first] = cit->second->clone(); 
		}
}

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
		_isListenSet = src._isListenSet;
		_isHostSet = src._isHostSet;
		_isServerNameSet = src._isServerNameSet;
		_isErrorPageSet = src._isErrorPageSet;
		_isClientMaxBodySizeSet = src._isClientMaxBodySizeSet;
		_isClientBodyInFileOnlySet = src._isClientBodyInFileOnlySet;
		_isClientBodyBufferSizeSet = src._isClientBodyBufferSizeSet;
		_isClientBodyTimeOutSet = src._isClientBodyTimeOutSet;
		
		for (map<string, ALocation*>::iterator it = _location.begin(); it != _location.end(); ++it) {
			delete it->second;
			_location.erase(it->first);
		}
		for (map<string, ALocation*>::const_iterator cit = src._location.begin(); cit != src._location.end(); ++cit) {
			_location[cit->first] = cit->second->clone(); 
		}
	}
	return (*this);
}

Server::~Server() {
	for (map<string, ALocation*>::iterator it = _location.begin(); it != _location.end(); ++it) {
		delete it->second;
	}
}

/* Setters ****************************************************************** */

void	Server::setListen( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		_listen.push_back(atoi((*it).c_str()));
	}
	_isListenSet = true;
}

void	Server::setHost( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		_host.push_back(*it);
	}
	_isHostSet = true;
}

void	Server::setServerName( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		_serverName.push_back(*it);
	}
	_isServerNameSet = true;
}

void	Server::setErrorPage( const vector<string>& tokens ) {
	string	path = tokens.back();
	if ((path.at(0) == '\'' || path.at(0) == '\"')
		&& path.at(0) == path.at(path.length() - 1))
		path = path.substr(1, path.length() - 2);
		
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end() - 1; ++it) {
		_errorPage.insert(make_pair(atoi((*it).c_str()), path));
	}
	_isErrorPageSet = true;
}

void	Server::setClientMaxBodySize( const vector<string>& tokens ) { 
	_clientMaxBodySize = atoi(tokens.at(2).c_str());
	_isClientMaxBodySizeSet = true;
}

void	Server::setClientBodyInFileOnly( const vector<string>& tokens ) {
	tokens.at(2) == "on" ? _clientBodyInFileOnly = true : _clientBodyInFileOnly = false;
	_isClientBodyInFileOnlySet = true;
}

void	Server::setClientBodyBufferSize( const vector<string>& tokens ) {
	_clientBodyBufferSize = atoi(tokens.at(2).c_str());
	_isClientBodyBufferSizeSet = true;
}

void	Server::setClientBodyTimeOut( const vector<string>& tokens ) {
	_clientBodyTimeOut = atoi(tokens.at(2).c_str());
	_isClientBodyTimeOutSet = true;
}

void	Server::addLocation( const vector<string>& tokens ) {
	if (tokens.at(2).at(0) == '~')
		_location[tokens.at(2)] = new Cgi();
	else if (tokens.at(2).find("upload") != string::npos)
		_location[tokens.at(2)] = new Upload();
	else
		_location[tokens.at(2)] = new StdLocation();
	
	_location[tokens.at(2)]->setPath(tokens);
}

void	Server::addLocation( const ALocation& location ) {
	_location[location.getPath()] = location.clone();
}

/* Getters ****************************************************************** */

int	Server::getListen( size_t idx ) const {
	if (idx >= _listen.size()) {
		stringstream ss;
		ss << "Index " << idx << " out of range for getListen()";
		throw (out_of_range(ss.str()));
	}
	return (_listen.at(idx));
}

vector<int>	Server::getListen( void ) const {
	return (_listen);
}

std::size_t		Server::getNbOfPorts() const {
	return (_listen.size());
}

string	Server::getHost( size_t idx ) const {
	if (idx >= _host.size()) {
		stringstream ss;
		ss << "Index " << idx << " out of range for getHost()";
		throw (out_of_range(ss.str()));
	}
	return (_host.at(idx));
}

vector<string>	Server::getHost( void ) const {
	return (_host);
}

string	Server::getServerName( size_t idx ) const {
	if (idx >= _serverName.size()) {
		stringstream ss;
		ss << "Index " << idx << " out of range for getServerName()";
		throw (out_of_range(ss.str()));
	}
	return (_serverName.at(idx));
}

vector<string>	Server::getServerName( void ) const {
	return (_serverName);
}

string	Server::getErrorPage( int code ) const {
	if (_errorPage.find(code) != _errorPage.end()) {
		return (_errorPage.at(code));
	}
	else {
		stringstream ss;
		ss << "Error page for code " << code << " not found";
		throw (invalid_argument(ss.str()));
	}
}

int	Server::getClientMaxBodySize( void ) const {
	return (_clientMaxBodySize);
}

bool	Server::getClientBodyInFileOnly( void ) const {
	return (_clientBodyInFileOnly);
}

int	Server::getClientBodyBufferSize( void ) const {
	return (_clientBodyBufferSize);
}

int	Server::getClientBodyTimeOut( void ) const {
	return (_clientBodyTimeOut);
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

/* Checking set locations *************************************************** */

bool	Server::isStdLocationSet( void ) const {
	for (map<string, ALocation*>::const_iterator cit = _location.begin(); cit != _location.end(); ++cit) {
		if (dynamic_cast<StdLocation*>(cit->second))
			return (true);
	}
	return (false);
}

bool	Server::isUploadSet( void ) const {
	for (map<string, ALocation*>::const_iterator cit = _location.begin(); cit != _location.end(); ++cit) {
		if (dynamic_cast<Upload*>(cit->second))
			return (true);
	}
	return (false);
}

bool	Server::isCgiSet( void ) const {
	for (map<string, ALocation*>::const_iterator cit = _location.begin(); cit != _location.end(); ++cit) {
		if (dynamic_cast<Cgi*>(cit->second))
			return (true);
	}
	return (false);
}

/* Methods ****************************************************************** */

void	Server::print( void ) const {
	cout << "listen: ";
	for (vector<int>::const_iterator cit = _listen.begin(); cit < _listen.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	cout << "host: ";
	for (vector<string>::const_iterator cit = _host.begin(); cit < _host.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	cout << "server_name: ";
	for (vector<string>::const_iterator cit = _serverName.begin(); cit < _serverName.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	for (map<int, string>::const_iterator cit = _errorPage.begin(); cit != _errorPage.end(); ++cit) {
		cout << "error_page " << cit->first << ": " << cit->second << endl;
	}
	cout << "client_max_body_size: " << _clientMaxBodySize << endl;
	cout << "client_body_in_file_only: " << _clientBodyInFileOnly << endl;
	cout << "client_body_buffer_size: " << _clientBodyBufferSize << endl;
	cout << "client_body_time_out: " << _clientBodyTimeOut << endl;
	for (map<string, ALocation*>::const_iterator cit = _location.begin(); cit != _location.end(); ++cit) {
		cit->second->print();
	}
	cout << endl;
}

void	Server::merge( Server& src ) {
	if (!_isListenSet)
		_listen = src._listen;
	if (!_isHostSet)
		_host = src._host;
	if (!_isServerNameSet)
		_serverName = src._serverName;
	if (!_isErrorPageSet)
		_errorPage = src._errorPage;
	if (!_isClientMaxBodySizeSet)
		_clientMaxBodySize = src._clientMaxBodySize;
	if (!_isClientBodyInFileOnlySet)
		_clientBodyInFileOnly = src._clientBodyInFileOnly;
	if (!_isClientBodyBufferSizeSet)
		_clientBodyBufferSize = src._clientBodyBufferSize;
	if (!_isClientBodyTimeOutSet)
		_clientBodyTimeOut = src._clientBodyTimeOut;
	for (map<string, ALocation*>::iterator it = _location.begin(); it != _location.end(); ++it) {
		it->second->merge(src);
	}
	if (!isStdLocationSet())
		addLocation(*src.getLocation("/"));
	if (!isUploadSet())
		addLocation(*src.getLocation("/upload"));
	if (!isCgiSet())
		addLocation(*src.getLocation("~\\.php$"));
}
