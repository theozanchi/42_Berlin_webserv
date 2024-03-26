/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/22 10:45:53 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

bool sigint_flag = false;

void    handle_sigint(int sig)
{
    (void)sig;
    std::cout << std::endl << "Sigint received" << std::endl;
    sigint_flag = true;
    return ;
}

int	main( int argc, char **argv )
{
	if (argc > 2)
	{
		cerr << "Invalid argument: only one configuration file accepted (optional)" << endl;
	}
	else
	{
		Configuration	config;
		Configuration	defaultConfig;

		try
		{
      			if (argc == 2)
			{
				Parser::parseFile(config, argv[1]);
			}
			Parser::parseFile(defaultConfig, "config/default.conf");
			config.merge(defaultConfig);
			config.print();

			int nb_of_servers = config.getNbOfServers();
			int nb_of_ports = 0;
    			std::cout << "Nb of Servers: " << nb_of_servers << std::endl;

			for (int i = 0; i < nb_of_servers; i++)
    			{
        			Server& config_info = config.getServer(i);
        			nb_of_ports += config_info.getNbOfPorts();
    			}

			std::cout << "Nb of Ports: " << nb_of_ports << std::endl;

			std::string *hosts = new std::string[nb_of_ports];
			int	*ports = new int[nb_of_ports];
			int	k = 0;

			for (int i = 0; i < nb_of_servers; i++)
    			{
        			Server& config_info = config.getServer(i);
        			int nb_server_ports = config_info.getNbOfPorts();

        			for (int j = 0; j < nb_server_ports; j++)
        			{
					hosts[k] = config_info.getHost(0);
					ports[k] = config_info.getListen(j);
					k++;
				}
			}

			for (int l = 0; l < k; l++)
			{
				std::cout << "Host: " << hosts[l] << " Ports: " << ports[l] << std::endl;
			}

			TCPServer aServer(ports, nb_of_ports, hosts);

			signal(SIGINT, &handle_sigint);
      			aServer.accept_connections();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (...)
		{
			std::cerr << "other kind of error" << std::endl;
		}
	}
}
