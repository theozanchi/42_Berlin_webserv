/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:12:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 16:51:42 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <vector>
# include <string>
# include <map>

using namespace std;

class ALocation;

class Server {
private:
	vector<int>				_listen;
	vector<string>			_host;
	vector<string>			_serverName;
	map<int, string>		_errorPage;
	int						_ClientMaxBodySize;
	bool					_ClientBodyInFileOnly;
	int						_ClientBodyBufferSize;
	int						_ClientBodyTimeOut;
	map<string, ALocation*>	_location;

public:
	Server();
	Server( const Server& src );
	Server& operator=( const Server& src );
	~Server();
};

#endif
