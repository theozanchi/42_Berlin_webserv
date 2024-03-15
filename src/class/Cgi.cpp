/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:37 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 12:32:28 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cgi.hpp"

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

/* Member functions ********************************************************* */
