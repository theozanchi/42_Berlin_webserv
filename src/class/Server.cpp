/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/27 15:58:00 by tzanchi          ###   ########.fr       */
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

/* Input validation ********************************************************* */

bool	Server::isValidListen( const string& token ) {
	if (token.length() == 0)
		return (false);
	for (string::const_iterator cit = token.begin(); cit < token.end(); ++cit) {
		if (!isdigit(*cit))
			return (false);
	}
	if (atoi(token.c_str()) < 0 || atoi(token.c_str()) > 65535)
		return (false);
	return (true);
}

bool	Server::isValidHost( const string& token ) {
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, token.c_str(), &(sa.sin_addr));
	if (result != 1) {
		return (false);
	}
	unsigned long ip = ntohl(sa.sin_addr.s_addr);
	if (ip >= 0x7F000000 && ip <= 0x7FFFFFFF) {
		return (true);
	}
	return (false);
}

bool	Server::isValidServerName( const string& token ) {
	for (string::const_iterator cit = token.begin(); cit < token.end(); ++cit) {
		if (isspace(*cit))
			return (false);
	}
	return (true);
}

bool	Server::isValidRoot( const string& token ) {
	if (access(token.c_str(), R_OK) == -1)
		return (false);
	return (true);
}

bool	Server::isValidErrorPagePath( const string& token ) {
	if (access(token.c_str(), R_OK) == -1)
		return (false);
	return (true);
}

bool	Server::isValidErrorPage( const string& token ) {
	if (token.length() == 0)
		return (false);
	for (string::const_iterator cit = token.begin(); cit < token.end(); ++cit) {
		if (!isdigit(*cit))
			return (false);
	}
	if (atoi(token.c_str()) < 100 || atoi(token.c_str()) > 599)
		return (false);
	return (true);
}

bool	Server::isValidClientMaxBodySize( const string& token ) {
	for (string::const_iterator cit = token.begin(); cit < token.end() - 1; ++cit) {
		if (!isdigit(*cit))
			return (false);
	}
	if (!isdigit(token.at(token.length() - 1))
		&& token.at(token.length() - 1) != 'K'
		&& token.at(token.length() - 1) != 'k'
		&& token.at(token.length() - 1) != 'M'
		&& token.at(token.length() - 1) != 'm'
		&& token.at(token.length() - 1) != 'G'
		&& token.at(token.length() - 1) != 'g')
		return (false);
	if (atoi(token.c_str()) < 0)
		return (false);
	return (true);
}

bool	Server::isValidClientBodyInFileOnly( const string& token ) {
	if (token != "on" && token != "1" && token != "yes"
		&& token != "off" && token != "0" && token != "no")
		return (false);
	return (true);
}

bool	Server::isValidClientBodyBufferSize( const string& token ) {
	for (string::const_iterator cit = token.begin(); cit < token.end() - 1; ++cit) {
		if (!isdigit(*cit))
			return (false);
	}
	if (!isdigit(token.at(token.length() - 1))
		&& token.at(token.length() - 1) != 'K'
		&& token.at(token.length() - 1) != 'k'
		&& token.at(token.length() - 1) != 'M'
		&& token.at(token.length() - 1) != 'm'
		&& token.at(token.length() - 1) != 'G'
		&& token.at(token.length() - 1) != 'g')
		return (false);
	if (atoi(token.c_str()) < 0)
		return (false);
	return (true);
}

bool	Server::isValidClientBodyTimeOut( const string& token ) {
	for (string::const_iterator cit = token.begin(); cit < token.end() - 1; ++cit) {
		if (!isdigit(*cit))
			return (false);
	}
	if (!isdigit(token.at(token.length() - 1))
		&& token.at(token.length() - 1) != 'S'
		&& token.at(token.length() - 1) != 's'
		&& token.at(token.length() - 1) != 'M'
		&& token.at(token.length() - 1) != 'm')
		return (false);
	if (atoi(token.c_str()) < 0)
		return (false);
	return (true);
}

/* Setters ****************************************************************** */

void	Server::setListen( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		if (!isValidListen(*it)) {
			stringstream ss;
			ss << "Warning: invalid " << *it << " port at line " << tokens.at(0) << ", using default value" << endl;
			throw (invalid_argument(ss.str()));
		}
		_listen.push_back(atoi((*it).c_str()));
	}
	_isListenSet = true;
}

void	Server::setHost( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		if (!isValidHost(*it)) {
			stringstream ss;
			ss << "Warning: invalid " << *it << " host at line " << tokens.at(0) << ", using default value" << endl;
			throw (invalid_argument(ss.str()));
		}
		_host.push_back(*it);
	}
	_isHostSet = true;
}

void	Server::setServerName( const vector<string>& tokens ) {
	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end(); ++it) {
		if (!isValidServerName(*it)) {
			stringstream ss;
			ss << "Warning: invalid " << *it << " server name at line " << tokens.at(0) << ", using default value" << endl;
			throw (invalid_argument(ss.str()));
		}
		_serverName.push_back(*it);
	}
	_isServerNameSet = true;
}

void	Server::setRoot( const vector<string>& tokens ) {
	string	path = tokens.back();
	if ((path.at(0) == '\'' || path.at(0) == '\"')
		&& path.at(0) == path.at(path.length() - 1))
		path = path.substr(1, path.length() - 2);
	if (!isValidRoot(path)) {
		stringstream ss;
		ss << "Warning: invalid " << path << " root path at line " << tokens.at(0) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	_root = path;
	_isRootSet = true;
}

void	Server::setErrorPage( const vector<string>& tokens ) {
	string	path = tokens.back();
	if ((path.at(0) == '\'' || path.at(0) == '\"')
		&& path.at(0) == path.at(path.length() - 1))
		path = path.substr(1, path.length() - 2);
	if (_root.at(_root.length() - 1) == '/')
		path = _root + path;
	else
		path = _root + "/" + path;
	if (!isValidErrorPagePath(path)) {
		stringstream ss;
		ss << "Warning: invalid " << path << " path at line " << tokens.at(0) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}

	for (vector<string>::const_iterator it = tokens.begin() + 2; it < tokens.end() - 1; ++it) {
		if (!isValidErrorPage(*it)) {
			stringstream ss;
			ss << "Warning: invalid " << *it << " error code at line " << tokens.at(0) << ", using default value" << endl;
			throw (invalid_argument(ss.str()));
		}
		_errorPage.insert(make_pair(atoi((*it).c_str()), path));
	}
	_isErrorPageSet = true;
}

void	Server::setClientMaxBodySize( const vector<string>& tokens ) { 
	if (!isValidClientMaxBodySize(tokens.at(2))) {
		stringstream ss;
		ss << "Warning: invalid client_max_body_size at line " << tokens.at(0) << ": " << tokens.at(2) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	char		unit = tokens.at(2).at(tokens.at(2).length() - 1);
	long long	multiplier = 1;

	switch (unit) {
		case 'K': multiplier = 1024; break;
		case 'k': multiplier = 1024 * 1024; break;
		case 'M': multiplier = 1024 * 1024; break;
		case 'm': multiplier = 1024 * 1024; break;
		case 'G': multiplier = 1024 * 1024 * 1024; break;
		case 'g': multiplier = 1024 * 1024 * 1024; break;
	}
	_clientMaxBodySize = atoi(tokens.at(2).c_str()) * multiplier;
	_isClientMaxBodySizeSet = true;
}

void	Server::setClientBodyInFileOnly( const vector<string>& tokens ) {
	if (!isValidClientBodyInFileOnly(tokens.at(2))) {
		stringstream ss;
		ss << "Warning: invalid client_body_in_file_only at line " << tokens.at(0) << ": " << tokens.at(2) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	if (tokens.at(2) == "on" || tokens.at(2) == "1" || tokens.at(2) == "yes")
		_clientBodyInFileOnly = true;
	else
		_clientBodyInFileOnly = false;
	_isClientBodyInFileOnlySet = true;
}

void	Server::setClientBodyBufferSize( const vector<string>& tokens ) {
	if (!isValidClientBodyBufferSize(tokens.at(2))) {
		stringstream ss;
		ss << "Warning: invalid client_body_buffer_size at line " << tokens.at(0) << ": " << tokens.at(2) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	char		unit = tokens.at(2).at(tokens.at(2).length() - 1);
	long long	multiplier = 1;

	switch (unit) {
		case 'K': multiplier = 1024; break;
		case 'k': multiplier = 1024 * 1024; break;
		case 'M': multiplier = 1024 * 1024; break;
		case 'm': multiplier = 1024 * 1024; break;
		case 'G': multiplier = 1024 * 1024 * 1024; break;
		case 'g': multiplier = 1024 * 1024 * 1024; break;
	}
	_clientBodyBufferSize = atoi(tokens.at(2).c_str()) * multiplier;
	_isClientBodyBufferSizeSet = true;
}

void	Server::setClientBodyTimeOut( const vector<string>& tokens ) {
	if (!isValidClientBodyTimeOut(tokens.at(2))) {
		stringstream ss;
		ss << "Warning: invalid client_body_time_out at line " << tokens.at(0) << ": " << tokens.at(2) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	char	unit = tokens.at(2).at(tokens.at(2).length() - 1);
	int		multiplier = 1;
	switch (unit) {
		case 'S': multiplier = 1; break;
		case 's': multiplier = 1; break;
		case 'M': multiplier = 60; break;
		case 'm': multiplier = 60; break;
	}
	_clientBodyTimeOut = atoi(tokens.at(2).c_str()) * multiplier;
	_isClientBodyTimeOutSet = true;
}

void	Server::addLocation( const vector<string>& tokens ) {
	string path = tokens.at(2);
	if (path.at(0) == '/')
		path = _root + path;
	else if (path.at(0) == '~')
		path = _root + path;
	else
		path = _root + "/" + path;
	if (tokens.at(2).at(0) == '~')
		_location[tokens.at(2)] = new Cgi();
	else if (tokens.at(2).find("upload") != string::npos)
		_location[tokens.at(2)] = new Upload();
	else
		_location[tokens.at(2)] = new StdLocation();
	
	_location[tokens.at(2)]->setPath(path);
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

string	Server::getRoot( void ) const {
	return (_root);
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
	cout << "root: " << _root << endl;
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
	if (!_isRootSet)
		_root = src._root;
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
