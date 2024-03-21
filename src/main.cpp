/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 14:54:47 by tzanchi          ###   ########.fr       */
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

int	main( int argc, char **argv ) {
	(void)argv;
	if (argc > 2) {
		cerr << "Invalid argument: only one configuration file accepted (optional)" << endl;
	}
	else {
		Configuration	config;

		try {
			Parser::parseFile(config, "config/default.conf");
			config.print();

			//int port[3] = { 8080, 9002, 8090 };
    		//int nb_of_ports = 3;
			//std::string hosts[3] = { "127.0.0.1", "127.1.0.1", "127.1.1.1" };

			//TCPServer aServer(port, nb_of_ports, hosts);
			TCPServer bServer(config);

			signal(SIGINT, &handle_sigint);
        	//aServer.accept_connections();
			bServer.accept_connections();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "other kind of error" << std::endl;
		}
	}
}
