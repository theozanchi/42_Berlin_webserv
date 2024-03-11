/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:42:06 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/11 12:49:29 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int	main( int argc, char **argv ) {
	(void)argv;
	if (argc > 2) {
		cerr << "Invalid argument: only one configuration file accepted (optional)" << endl;
	}
	else {
		Configuration*	config = new Configuration();
	
		try {
			Parser::parseFile(config, "config/default.conf");
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}
