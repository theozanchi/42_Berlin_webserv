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

int	main( int argc, char **argv ) {
	if (argc > 2) {
		cerr << "Invalid argument: only one configuration file accepted (optional)" << endl;
	}
	else {
		Configuration	config;
		Configuration	defaultConfig;

		try {
			if (argc == 2) {
				Parser::parseFile(config, argv[1]);
			}
			Parser::parseFile(defaultConfig, "config/default.conf");
			config.merge(defaultConfig);
			config.print();

			int port[3] = { 8080, 9002, 8090 };
    		int nb_of_ports = 3;

			TCPServer aServer(port, nb_of_ports);

			signal(SIGINT, &handle_sigint);
        	aServer.accept_connections();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
		catch (...) {
			std::cerr << "other kind of error" << std::endl;
		}
	}
}
