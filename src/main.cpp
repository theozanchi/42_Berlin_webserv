/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/21 09:45:47 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main( int argc, char **argv ) {
	(void)argv;
	if (argc > 2) {
		cerr << "Invalid argument: only one configuration file accepted (optional)" << endl;
	}
	else {
		Configuration	defaultConfig;
		// Configuration	userConfig;
	
		try {
			Parser::parseFile(defaultConfig, "config/default.conf");
			// if (argc == 2) {
			// 	Parser::parseFile(userConfig, argv[1]);
			// 	config.merge(userConfig);
			// }
			defaultConfig.print();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
