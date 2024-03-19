/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/19 10:55:20 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>
# include <functional>

using namespace std;

class ALocation;

class Server {
private:
	vector<int>				_listen;
	vector<string>			_host;
	vector<string>			_serverName;
	map<int, string>		_errorPage;
	int						_clientMaxBodySize;
	bool					_clientBodyInFileOnly;
	int						_clientBodyBufferSize;
	int						_clientBodyTimeOut;
	map<string, ALocation*>	_location;

public:
	Server();
	Server( const Server& src );
	Server& operator=( const Server& src );
	~Server();

	void	setListen( const vector<string>& tokens );
	void	setHost( const vector<string>& tokens );
	void	setServerName( const vector<string>& tokens );
	void	setErrorPage( const vector<string>& tokens );
	void	setClientMaxBodySize( const vector<string>& tokens );
	void	setClientBodyInFileOnly( const vector<string>& tokens );
	void	setClientBodyBufferSize( const vector<string>& tokens );
	void	setClientBodyTimeOut( const vector<string>& tokens );

	void		addLocation( const vector<string>& tokens );
	ALocation*	getLocation( const string& path_or_flag );
};

#endif
