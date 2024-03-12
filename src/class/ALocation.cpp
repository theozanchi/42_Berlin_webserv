/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:42:06 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ALocation.hpp"

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
