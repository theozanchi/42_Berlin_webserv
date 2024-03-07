/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:50:17 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 14:51:33 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Upload.hpp"

/* Constructors, assignment operator and destructor ************************* */

Upload::Upload() : ALocation() {}

Upload::Upload( const Upload& src ) : ALocation(src) { *this = src; }

Upload& Upload::operator=( const Upload& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

Upload::~Upload() {}

/* Member functions ********************************************************* */
