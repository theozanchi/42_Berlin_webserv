/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:52:21 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 14:52:55 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "StdLocation.hpp"

/* Constructors, assignment operator and destructor ************************* */

StdLocation::StdLocation() : ALocation() {}

StdLocation::StdLocation( const StdLocation& src ) : ALocation(src) { *this = src; }

StdLocation& StdLocation::operator=( const StdLocation& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

StdLocation::~StdLocation() {}

/* Member functions ********************************************************* */
