/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:50:17 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 10:55:14 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Upload.hpp"

/* Constructors, assignment operator and destructor ************************* */

Upload::Upload() : ALocation() {}

Upload::Upload( const Upload& src )
	:	ALocation(src),
		_uploadStore(src._uploadStore)
	{}

Upload& Upload::operator=( const Upload& src ) {
	if (this != &src) {
		ALocation::operator=(src);
		_uploadStore = src._uploadStore;
	}
	return (*this);
}

Upload::~Upload() {}

/* Member functions ********************************************************* */

void	Upload::setUploadStore( const vector<string>& tokens ) {
	string	uploadStore = tokens.at(1);

	if ((uploadStore.front() == '\'' || uploadStore.front() == '\"')
		&& uploadStore.front() == uploadStore.back())
		uploadStore = uploadStore.substr(1, uploadStore.length() - 2);
	_uploadStore = uploadStore;
}
