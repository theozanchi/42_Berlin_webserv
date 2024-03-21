/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:00:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 14:56:43 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

Configuration::Configuration() {}

Configuration::Configuration( const Configuration& src )
	:	_server( src._server )
	{}

Configuration& Configuration::operator=( const Configuration& src ) {
	if (this != &src) {
		_server = src._server;
	}
	return (*this);
}

Configuration::~Configuration() {}

/* Setters ****************************************************************** */

void	Configuration::addServer( void ) {
	_server.push_back(Server());
}

/* Getters ****************************************************************** */

Server&	Configuration::getServer( size_t idx ) {
	if (idx < _server.size()) {
		return (_server[idx]);
	}
	else {
		throw (invalid_argument("Invalid index for getServer()"));
	}
}

Server&	Configuration::getServer( const string& flag ) {
	if (flag == "LAST") {
		return (_server.back());
	}
	else {
		throw (invalid_argument("Invalid flag for getServer()"));
	}
}

std::size_t	Configuration::getNbOfServers() {
	return (_server.size());
}

/* Methods ****************************************************************** */

void	Configuration::print( void ) const {
	cout << "\033[1;32mConfiguration\033[0m" << endl;
	size_t server_count = 0;
	for (vector<Server>::const_iterator cit = _server.begin(); cit < _server.end(); ++cit) {
		cout << "\033[1;34mServer " << server_count++ << "\033[0m" << endl;
		(*cit).print();
	}
}
