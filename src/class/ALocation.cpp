/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/27 15:56:41 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

ALocation::ALocation() 
	:	_autoIndex(false), 
		_isPathSet(false),
		_isAllowSet(false),
		_isAutoIndexSet(false) {}

ALocation::ALocation( const ALocation& src )
	:	_path(src._path),
		_allow(src._allow),
		_autoIndex(src._autoIndex),
		_isPathSet(src._isPathSet),
		_isAllowSet(src._isAllowSet),
		_isAutoIndexSet(src._isAutoIndexSet) {}

ALocation& ALocation::operator=( const ALocation& src ) {
	if (this != &src) {
		_path = src._path;
		_allow = src._allow;
		_autoIndex = src._autoIndex;
		_isPathSet = src._isPathSet;
		_isAllowSet = src._isAllowSet;
		_isAutoIndexSet = src._isAutoIndexSet;
	}
	return (*this);
}

ALocation::~ALocation() {}

/* Breakline **************************************************************** */

bool	ALocation::isValidPath( const string& token, int type ) {
	if (access(token.c_str(), type) == -1)
		return (false);
	return (true);
}

bool	ALocation::isValidAllow( const string& token ) {
	if (token != "GET"
		&& token != "POST"
		&& token != "DELETE")
		return (false);
	return (true);
}

bool	ALocation::isValidAutoIndex( const string& token ) {
	if (token != "on" && token != "1" && token != "yes"
		&& token != "off" && token != "0" && token != "no")
		return (false);
	return (true);
}

/* Setters ****************************************************************** */

void	ALocation::setPath( const vector<string>& tokens ) {
	string	type = this->getType();
	if ((type == "StdLocation" && !isValidPath(tokens.at(2), F_OK))
		|| (type == "Upload" && !isValidPath(tokens.at(2), W_OK))) {
		stringstream ss;
		ss << "Warning: invalid " << tokens.at(2) << " path at line " << tokens.at(0) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	_path = tokens.at(2);
	_isPathSet = true;
}

void	ALocation::setPath( const string& path ) {
	string	type = this->getType();
	if ((type == "StdLocation" && !isValidPath(path, F_OK))
		|| (type == "Upload" && !isValidPath(path, W_OK))) {
		stringstream ss;
		ss << "Warning: invalid " << path << " for location, using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	_path = path;
	_isPathSet = true;
}

void	ALocation::setAllow( const vector<string>& tokens ) {
	vector<string>	bin;
	for (vector<string>::const_iterator cit = tokens.begin() + 2; cit < tokens.end(); ++cit) {
		if (isValidAllow(*cit))
			_allow.push_back(*cit);
		else
			bin.push_back(*cit);
	}
	if (bin.size() > 0) {
		stringstream ss;
		ss << "Warning: invalid method";
		if (bin.size() > 1)
			ss << "s";
		ss << " ";
		for (vector<string>::const_iterator cit = bin.begin(); cit < bin.end(); ++cit) {
			ss << *cit;
			if (cit + 1 < bin.end())
				ss << ", ";
		}
		ss << " at line " << tokens.at(0) << ", ignored" << endl;
		throw (invalid_argument(ss.str()));
	}
	if (_allow.size() > 0)
		_isAllowSet = true;
}

void	ALocation::setAutoIndex( const vector<string>& tokens ) {
	if (!isValidAutoIndex(tokens.at(2))) {
		stringstream ss;
		ss << "Warning: invalid "<< tokens.at(2) << " autoindex value at line " << tokens.at(0) << ", using default value" << endl;
		throw (invalid_argument(ss.str()));
	}
	if (tokens.at(2) == "on" || tokens.at(2) == "1" || tokens.at(2) == "yes")
		_autoIndex = true;
	else
		_autoIndex = false;
	_isAutoIndexSet = true;
}

/* Getters ****************************************************************** */

string	ALocation::getPath( void ) const {
	return (_path);
}

string	ALocation::getAllow( size_t idx ) const {
	if (idx >= _allow.size()) {
		stringstream ss;
		ss << "Index " << idx << " out of range for getAllow()";
		throw (out_of_range(ss.str()));
	}
	return (_allow.at(idx));
}

vector<string>	ALocation::getAllow( void ) const {
	return (_allow);
}

bool	ALocation::isAllowed( const string& method ) const {
	for (vector<string>::const_iterator cit = _allow.begin(); cit < _allow.end(); ++cit) {
		if (*cit == method)
			return (true);
	}
	return (false);
}

bool	ALocation::getAutoIndex( void ) const {
	return (_autoIndex);
}

string	ALocation::getType( void ) const {
	if (dynamic_cast<const StdLocation*>(this))
		return ("StdLocation");
	else if (dynamic_cast<const Upload*>(this))
		return ("Upload");
	else if (dynamic_cast<const Cgi*>(this))
		return ("Cgi");
	else
		return ("Unknown");
}

/* Methods ****************************************************************** */

void	ALocation::merge( Server& src ) {
	string	type = getType();
	
	if (type == "StdLocation")
		dynamic_cast<StdLocation*>(this)->merge(dynamic_cast<StdLocation*>(src.getLocation("/")));
	else if (type == "Upload")
		dynamic_cast<Upload*>(this)->merge(dynamic_cast<Upload*>(src.getLocation("/upload")));
	else if (type == "Cgi")
		dynamic_cast<Cgi*>(this)->merge(dynamic_cast<Cgi*>(src.getLocation("~\\.php$")));
	else
		throw (invalid_argument("Unknown location type"));
}
