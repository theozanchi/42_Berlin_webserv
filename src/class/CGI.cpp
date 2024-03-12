/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:37 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/12 16:46:21 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CGI.hpp"

/* Constructors, assignment operator and destructor ************************* */

CGI::CGI() : ALocation() {}

CGI::CGI( const CGI& src ) : ALocation(src) {}

CGI& CGI::operator=( const CGI& src ) {
	if (this != &src) {
		ALocation::operator=(src);
	}
	return (*this);
}

CGI::~CGI() {}

/* Member functions ********************************************************* */
