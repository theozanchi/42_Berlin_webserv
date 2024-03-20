/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 17:15:08 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

ALocation::ALocation() {
	_autoIndex = false;
}

ALocation::ALocation( const ALocation& src )
	:	_path(src._path),
		_allow(src._allow),
		_autoIndex(src._autoIndex)
	{}

ALocation& ALocation::operator=( const ALocation& src ) {
	if (this != &src) {
		_path = src._path;
		_allow = src._allow;
		_autoIndex = src._autoIndex;
	}
	return (*this);
}

ALocation::~ALocation() {}

/* Setters ****************************************************************** */

void	ALocation::setPath( const vector<string>& tokens ) {
	_path = tokens.at(2);
}

void	ALocation::setAllow( const vector<string>& tokens ) {
	for (vector<string>::const_iterator cit = tokens.begin() + 2; cit < tokens.end(); ++cit) {
		_allow.push_back(*cit);
	}
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
