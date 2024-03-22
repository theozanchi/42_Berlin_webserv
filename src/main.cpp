/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 10:33:50 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

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
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
