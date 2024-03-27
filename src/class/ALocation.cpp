/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/26 17:42:20 by tzanchi          ###   ########.fr       */
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

// bool	ALocation::isValidPath( const string& token ) {
	
// }

/* Setters ****************************************************************** */

void	ALocation::setPath( const vector<string>& tokens ) {
	_path = tokens.at(2);
	_isPathSet = true;
}

void	ALocation::setPath( const string& path ) {
	_path = path;
	_isPathSet = true;
}

void	ALocation::setAllow( const vector<string>& tokens ) {
	for (vector<string>::const_iterator cit = tokens.begin() + 2; cit < tokens.end(); ++cit) {
		_allow.push_back(*cit);
	}
	_isAllowSet = true;
}

void	ALocation::setAutoIndex( const vector<string>& tokens ) {
	if (tokens.at(2) == "on")
		_autoIndex = true;
	else if (tokens.at(2) == "off")
		_autoIndex = false;
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": \"" << tokens.at(1) << "\"not supported";
		throw (ss.str());
	}
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

bool	ALocation::isAllow( const string& method ) const {
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
