/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:50:17 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/28 12:41:17 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* Constructors, assignment operator and destructor ************************* */

Upload::Upload( const Server& server ) : ALocation(server) {}

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

/* Input validation ********************************************************* */

bool	Upload::isValidUploadStore( const string& token ) {
	if (access(token.c_str(), R_OK) == -1)
		return (false);
	return (true);
}

/* Setters ****************************************************************** */

void	Upload::setUploadStore( const vector<string>& tokens ) {
	string	path = tokens.at(2);

	if ((path.at(0) == '\'' || path.at(0) == '\"')
		&& path.at(0) == path.at(path.length() - 1))
		path = path.substr(1, path.length() - 2);
	if (path.at(path.length() - 1) == '/')
		path = _server.getRoot() + path;
	else
		path = _server.getRoot() + "/" + path;

	if (!isValidUploadStore(path)) {
		stringstream ss;
		ss << "Warning: invalid " << tokens.at(2) << " upload path at line " << tokens.at(0) << ", using default value";
		throw (invalid_argument(ss.str()));
	}
	_uploadStore = path;
	_isUploadStoreSet = true;
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

void	Upload::merge( Upload* src ) {
	if (src == NULL)
		throw (logic_error("Impossible to merge a NULL location"));
	if (!_isPathSet)
		_path = src->_path;
	if (!_isAllowSet)
		_allow = src->_allow;
	if (!_isAutoIndexSet)
		_autoIndex = src->_autoIndex;
	if (!_isUploadStoreSet)
		_uploadStore = src->_uploadStore;
}