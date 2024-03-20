/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:50:17 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 17:16:25 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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

/* Setters ****************************************************************** */

void	Upload::setUploadStore( const vector<string>& tokens ) {
	string	uploadStore = tokens.at(2);

	if ((uploadStore.at(0) == '\'' || uploadStore.at(0) == '\"')
		&& uploadStore.at(0) == uploadStore.at(uploadStore.length() - 1))
		uploadStore = uploadStore.substr(1, uploadStore.length() - 2);
	_uploadStore = uploadStore;
}


/* Getters ****************************************************************** */

string	Upload::getUploadStore( void ) const {
	return (_uploadStore);
}

/* Methods ****************************************************************** */

void	Upload::print( void ) const {
	cout << "\033[1;36mUpload\033[0m" << endl;
	cout << "\tpath: " << _path << endl;
	cout << "\tallow: ";
	for (vector<string>::const_iterator cit = _allow.begin(); cit < _allow.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
	cout << "\tauto_index: " << _autoIndex << endl;
	cout << "\tupload_store: " << _uploadStore << endl;
}

Upload*	Upload::clone( void ) const {
	return (new Upload(*this));
}
