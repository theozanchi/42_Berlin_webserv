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

Request::Request(std::string &httpRequest)
{
	std::vector<std::string> request;
	if (httpRequest.empty())
		throw badRequest();

	size_t i = httpRequest.find("\n");
	std::string firstString = httpRequest.substr(0, i);
	std::cout << "\nReceived a request: " << firstString << std::endl;
	std::cout << "----------------------" << std::endl;
	std::cout << "PARSING:" << std::endl;
	this->parseFirstString(firstString);
	httpRequest.erase(0, i + 1);
	std::cout << "----------------------" << std::endl;
	std::cout << "\nRequest new:\n'" << httpRequest << "'" << std::endl;
}

void Request::parseFirstString(std::string &httpRequest)
{
	// Parsing Method
	size_t i = httpRequest.find(' ');
	if (i == std::string::npos)
		throw (badRequest());
	std::string tmp_method = httpRequest.substr(0, i);
	if (tmp_method == "GET")
		_method = GET;
	else if (tmp_method == "POST")
		_method = POST;
	else if (tmp_method == "DELETE")
		_method = DELETE;
	else
		throw (badRequest());
	httpRequest.erase(0, i + 1);

	// Parsing path(url)
	i = httpRequest.find(' ');
	if (i == std::string::npos)
	{
		i = httpRequest.length() - 1;
		_path = httpRequest.substr(0, i);
		return ;
	}
	else
	{
		_path = httpRequest.substr(0, i);
		httpRequest.erase(0, i + 1);
	}

	// Checking HTTP protocol is used
	i = httpRequest.find('/');
	std::string tmpProtocol = httpRequest.substr(0, i);
	if (tmpProtocol != "HTTP" && tmpProtocol != "http")
		throw (badRequest());

	// Parsing (HTTP-Version)
	i = httpRequest.length() - 1;
	size_t start = 0;
	while (std::isdigit(httpRequest[start]) == 0 && start < i)
		start++;
	if (start >= i)
		throw (badRequest());
	_httpVersion = atof(httpRequest.substr(start, i).c_str());
	httpRequest.erase(0, i);
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