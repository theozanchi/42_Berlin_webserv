/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:48 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 11:35:52 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ALocation.hpp"

/* Constructors, assignment operator and destructor ************************* */

ALocation::ALocation() {}

ALocation::ALocation( const ALocation& src ) { *this = src; }

ALocation& ALocation::operator=( const ALocation& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

ALocation::~ALocation() {}

/* Member functions ********************************************************* */
