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
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
