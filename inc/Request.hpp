/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 12:34:14 by ole               #+#    #+#             */
/*   Updated: 2024/03/11 15:42:00 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <exception>
#include <cstdlib>
#include <sstream>

enum method
{
	GET,
	POST,
	DELETE
};

class Request
{
private:
	int	_method;
	std::string	_path;
	float		_httpVersion;
	std::map<std::string, std::string>	_httpHeaders;


public:
	Request(std::string &httpRequest);
//	~Request();
//	Request(const Request & copy);
//	Request & operator=(const Request & copy);

	class badRequest : public std::exception
	{
		public:
			virtual const char* what() const throw()
			{
				return ("Error: Bad request");
			}
	};
	void parseFirstString(std::string &httpRequest);
};