/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:21 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 10:55:20 by tzanchi          ###   ########.fr       */
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

/* Member functions ********************************************************* */

void	StdLocation::setIndex( const vector<string>& tokens ) {
	string	index = tokens.at(1);

	if ((index.front() == '\'' || index.front() == '\"')
		&& index.front() == index.back())
		index = index.substr(1, index.length() - 2);
	_index = index;
}
