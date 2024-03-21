/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:37 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 08:55:47 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

Cgi::Cgi() : ALocation() {}

Cgi::Cgi( const Cgi& src ) : ALocation(src) {}

Cgi& Cgi::operator=( const Cgi& src ) {
	if (this != &src) {
		ALocation::operator=(src);
	}
	return (*this);
}

Cgi::~Cgi() {}

/* Methods ****************************************************************** */

Cgi*	Cgi::clone( void ) const {
	return (new Cgi(*this));
}

void	Cgi::print( void ) const {
	cout << "\033[1;36mCgi\033[0m" << endl;
	cout << "\tpath: " << _path << endl;
	cout << "\tallow: ";
	for (vector<string>::const_iterator cit = _allow.begin(); cit < _allow.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	cout << "\tauto_index: " << _autoIndex << endl;
}
