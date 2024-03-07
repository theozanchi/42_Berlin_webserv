/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 10:04:44 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Configuration.hpp"

/* Constructors, assignment operator and destructor ************************* */

Configuration::Configuration() {}

Configuration::Configuration( const Configuration& src ) { *this = src; }

Configuration& Configuration::operator=( const Configuration& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

Configuration::~Configuration() {}

/* Member functions ********************************************************* */
