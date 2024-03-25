/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/25 19:21:19 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>
# include <functional>
# include <arpa/inet.h>
# include <unistd.h>

using namespace std;

class ALocation;

class Server {
private:
	vector<int>				_listen;
	vector<string>			_host;
	vector<string>			_serverName;
	map<int, string>		_errorPage;
	long long				_clientMaxBodySize;
	bool					_clientBodyInFileOnly;
	int						_clientBodyBufferSize;
	int						_clientBodyTimeOut;
	map<string, ALocation*>	_location;

	bool					_isListenSet, _isHostSet, _isServerNameSet, \
							_isErrorPageSet, _isClientMaxBodySizeSet, \
							_isClientBodyInFileOnlySet, _isClientBodyBufferSizeSet, \
							_isClientBodyTimeOutSet;

	bool					isValidListen( const string& token );
	bool					isValidHost( const string& token );
	bool					isValidServerName( const string& token );
	bool					isValidErrorPagePath( const string& token );
	bool					isValidErrorPage( const string& token );
	bool					isValidClientMaxBodySize( const string& token );
	bool					isValidClientBodyInFileOnly( const string& token );
	bool					isValidClientBodyBufferSize( const string& token );
	bool					isValidClientBodyTimeOut( const string& token );

	bool					isStdLocationSet( void ) const;
	bool					isUploadSet( void ) const;
	bool					isCgiSet( void ) const;

public:
	Server();
	Server( const Server& src );
	Server& operator=( const Server& src );
	~Server();

	void			setListen( const vector<string>& tokens );
	void			setHost( const vector<string>& tokens );
	void			setServerName( const vector<string>& tokens );
	void			setErrorPage( const vector<string>& tokens );
	void			setClientMaxBodySize( const vector<string>& tokens );
	void			setClientBodyInFileOnly( const vector<string>& tokens );
	void			setClientBodyBufferSize( const vector<string>& tokens );
	void			setClientBodyTimeOut( const vector<string>& tokens );
	void			addLocation( const vector<string>& tokens );
	void			addLocation( const ALocation& location );

	int				getListen( size_t idx ) const;
	std::size_t		getNbOfPorts() const;
	vector<int>		getListen( void ) const;
	string			getHost( size_t idx ) const;
	vector<string>	getHost( void ) const;
	string			getServerName( size_t idx ) const;
	vector<string>	getServerName( void ) const;
	string			getErrorPage( int code ) const;
	int				getClientMaxBodySize( void ) const;
	bool			getClientBodyInFileOnly( void ) const;
	int				getClientBodyBufferSize( void ) const;
	int				getClientBodyTimeOut( void ) const;
	ALocation*		getLocation( const string& path_or_flag );

	void			print( void ) const;
	void			merge( Server& src );
};

#endif
