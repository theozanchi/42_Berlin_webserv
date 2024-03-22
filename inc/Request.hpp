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

#define RED "\033[0;38;5;9m"
#define GRN "\033[0;38;5;2m"
#define BLU "\033[0;38;5;14m"
#define YEL "\033[0;38;5;11m"
#define RES "\e[0m"

enum method
{
	GET,
	POST,
	DELETE
};

class Request
{
private:
	int			_method;
	std::string	_uri;
	float		_httpVersion;
	std::string _hostName;
	std::string _requestBody;
	std::map<std::string, std::string>	_httpHeaders;

public:
	Request();
	Request(std::string &httpRequest);
	~Request();
	Request(const Request & copy);
	Request & operator=(const Request & copy);

	int getMethod() const;
	std::string	const getUri() const;
	float getVersion() const;
	std::string const getHostname() const;
	std::string const getRequestBody() const;
	std::map<std::string, std::string> const getHttpHeaders() const;

	void parseFirstString(std::string &httpRequest);
	void parseKeyValue(std::string &header);
	void parseHostName();
	void parseBody(std::string &header);

	class badRequest : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request");
		}
	};

	class badRequestHeader : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request: invalid header format");
		}
	};

	class badRequestEmpty : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request: Empty request");
		}
	};

	class badRequestMethod : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request: Wrond method. Accepted methods: GET, POST, DELETE");
		}
	};

	class badRequestNotHttp : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request: Protocol needs to be HTTP");
		}
	};

	class badRequestHttpVersion : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad request: Wrong HTTP version");
		}
	};
};

std::ostream & operator<<(std::ostream &ostr, Request const &request);