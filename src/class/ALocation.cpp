/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 10:48:11 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

ALocation::ALocation() {}

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

/* Member functions ********************************************************* */

void	ALocation::setPath( const vector<string>& tokens ) {
	_path = tokens.at(1);
}

void	ALocation::setAllow( const vector<string>& tokens ) {
	for (vector<string>::const_iterator cit = tokens.begin() + 1; cit < tokens.end(); ++cit) {
		_allow.push_back(*cit);
	}
}

void	ALocation::setAutoIndex( const vector<string>& tokens ) {
	if (tokens.at(1) == "on")
		_autoIndex = true;
	else if (tokens.at(1) == "off")
		_autoIndex = false;
	else {
		stringstream ss;
		ss << "Invalid config at line " << tokens.at(0) << ": \"" << tokens.at(1) << "\"not supported";
		throw (ss.str());
	}
}
