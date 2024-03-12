/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:21 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:45:36 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StdLocation.hpp"

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
