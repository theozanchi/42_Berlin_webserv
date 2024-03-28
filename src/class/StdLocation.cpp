/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:21 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/27 16:23:02 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

StdLocation::StdLocation( const Server& server ) : ALocation(server), _isIndexSet(false) {}

StdLocation::StdLocation( const StdLocation& src )
	:	ALocation(src),
		_index(src._index),
		_isIndexSet(src._isIndexSet)
	{}

StdLocation& StdLocation::operator=( const StdLocation& src ) {
	if (this != &src) {
		ALocation::operator=(src);
		_index = src._index;
		_isIndexSet = src._isIndexSet;
	}
	return (*this);
}

StdLocation::~StdLocation() {}

/* Input validation ********************************************************* */

bool	StdLocation::isValidIndex( const string& token ) {
	if (access(token.c_str(), R_OK) == -1)
		return (false);
	return (true);
}

/* Setters ****************************************************************** */

void	StdLocation::setIndex( const vector<string>& tokens ) {
	string	path = tokens.at(2);

	if ((path.at(0) == '\'' || path.at(0) == '\"')
		&& path.at(0) == path.at(path.length() - 1))
		path = path.substr(1, path.length() - 2);
	if (path.at(path.length() - 1) == '/')
		path = _server.getRoot() + path;
	else
		path = _server.getRoot() + "/" + path;

	if (!isValidIndex(path)) {
		stringstream ss;
		ss << "Warning: invalid " << tokens.at(2) << " index path at line " << tokens.at(0) << ", using default value";
		throw (invalid_argument(ss.str()));
	}
	_index = path;
	_isIndexSet = true;
}


/* Getters ****************************************************************** */

string	StdLocation::getIndex( void ) const {
	return (_index);
}

/* Methods ****************************************************************** */

void	StdLocation::print( void ) const {
	cout << "\033[1;36mstandard location\033[0m" << endl;
	cout << "\tpath: " << _path << endl;
	cout << "\tallow: ";
	for (vector<string>::const_iterator cit = _allow.begin(); cit < _allow.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	cout << "\tindex: " << _index << endl;
	cout << "\tauto_index: " << _autoIndex << endl;
}

StdLocation*	StdLocation::clone( void ) const {
	return (new StdLocation(*this));
}

void	StdLocation::merge( StdLocation* src ) {
	if (src == NULL)
		throw (logic_error("Impossible to merge a NULL location"));
	if (!_isPathSet)
		_path = src->_path;
	if (!_isAllowSet)
		_allow = src->_allow;
	if (!_isAutoIndexSet)
		_autoIndex = src->_autoIndex;
	if (!_isIndexSet)
		_index = src->_index;
}
