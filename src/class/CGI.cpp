/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:37 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 14:51:20 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

/* Constructors, assignment operator and destructor ************************* */

CGI::CGI() : ALocation() {}

CGI::CGI( const CGI& src ) : ALocation(src) { *this = src; }

CGI& CGI::operator=( const CGI& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

CGI::~CGI() {}

/* Member functions ********************************************************* */
