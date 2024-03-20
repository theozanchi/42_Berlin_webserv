/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:21 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 15:49:57 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

StdLocation::StdLocation() : ALocation() {}

StdLocation::StdLocation( const StdLocation& src )
	:	ALocation(src),
		_index(src._index)
	{}

StdLocation& StdLocation::operator=( const StdLocation& src ) {
	if (this != &src) {
		ALocation::operator=(src);
		_index = src._index;
	}
	return (*this);
}

StdLocation::~StdLocation() {}

/* Setters ****************************************************************** */

void	StdLocation::setIndex( const vector<string>& tokens ) {
	string	index = tokens.at(2);

	if ((index.at(0) == '\'' || index.at(0) == '\"')
		&& index.at(0) == index.at(index.length() - 1))
		index = index.substr(1, index.length() - 2);
	_index = index;
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
