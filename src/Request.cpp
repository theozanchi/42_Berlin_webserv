/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:39:54 by ole               #+#    #+#             */
/*   Updated: 2024/03/11 12:40:10 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(std::string httpRequest)
{
	std::vector<std::string> request;

	std::cout << "Received a request: " << httpRequest << std::endl;
}

/*
stringVector getStringTokens(std::string const &s, char c)
{
	stringVector tokens;
	std::stringstream ss(s);
	std::string token;

	while (std::getline(ss, token, c))
	{
		if (!token.empty())
			tokens.push_back(token);
	}
	return tokens;
}
*/