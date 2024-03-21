/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Configuration.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:59:46 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 13:10:33 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIGURATION_HPP
# define CONFIGURATION_HPP

# include <string>
# include <vector>

using namespace std;

class Server;

class Configuration {
private:
	vector<Server>	_server;

public:
	Configuration();
	Configuration( const Configuration& src );
	Configuration& operator=( const Configuration& src );
	~Configuration();

	void	addServer( void );

	Server&	getServer( size_t idx );
	Server&	getServer( const string& flag );
	std::size_t	getNbOfServers(); // needed for TCP Server Constructor

	void	print( void ) const;
};

#endif
