/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:30 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 16:49:19 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "ALocation.hpp"
#include "StdLocation.hpp"
#include "Upload.hpp"
#include "CGI.hpp"

/* Constructors, assignment operator and destructor ************************* */

Server::Server() {}

Server::Server( const Server& src ) { *this = src; }

Server& Server::operator=( const Server& src ) {
	if (this != &src) {
		*this = src;
	}
	return (*this);
}

Server::~Server() {}

/* Member functions ********************************************************* */
