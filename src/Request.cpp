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

Request::Request() {}

Request::Request(std::string &httpRequest) {
	std::string firstString;
	std::string header;
	size_t i;

	// Check if the http request is empty
	if (httpRequest.empty())
		throw (badRequestEmpty());

	// Parsing the first string and cutting it off
	i = httpRequest.find("\n");
	firstString = httpRequest.substr(0, i);
	this->parseFirstString(firstString);
	httpRequest.erase(0, i + 1);

	// Parsing the rest of the header and cutting it off
	while ((i = httpRequest.find("\n")) != std::string::npos)
	{
		header = httpRequest.substr(0, i);
		//std::cout << "Header: " << header << std::endl;
		if (header.empty() || header[0] == '\r')
			break;
		this->parseKeyValue(header);
		httpRequest.erase(0, i + 1);
	}
	if (i == std::string::npos)
	{
		header = httpRequest.substr(0, httpRequest.length());
		this->parseKeyValue(header);
		httpRequest.erase(0, httpRequest.length());
	}
	else
	{
		header = httpRequest.substr(0, i);
		this->parseKeyValue(header);
		httpRequest.erase(0, i + 1);
	}

	// Parsing host name
	this->parseHostName();

	// Parsing body (if exists)
	if (!httpRequest.empty())
		this->parseBody(httpRequest);
}

Request::Request(Request const & copy) { *this = copy; }

Request & Request::operator=(const Request & copy)
{
	this->_method = copy._method;
	this->_uri = copy._uri;
	this->_httpVersion = copy._httpVersion;
	this->_httpHeaders = copy._httpHeaders;

	return (*this);
}

Request::~Request(){}

void Request::parseFirstString(std::string &firstString)
{
	// Parsing Method
	size_t i = firstString.find(' ');
	if (i == std::string::npos)
		throw (badRequest());
	std::string tmp_method = firstString.substr(0, i);
	if (tmp_method == "GET")
		_method = GET;
	else if (tmp_method == "POST")
		_method = POST;
	else if (tmp_method == "DELETE")
		_method = DELETE;
	else
		throw (badRequestMethod());
	firstString.erase(0, i + 1);

	// Parsing path(url)
	i = firstString.find(' ');
	if (i == std::string::npos)
	{
		i = firstString.length() - 1;
		_uri = firstString.substr(0, i);
		return ;
	}
	else
	{
		_uri = firstString.substr(0, i);
		firstString.erase(0, i + 1);
	}

	// Checking HTTP protocol is used
	i = firstString.find('/');
	std::string tmpProtocol = firstString.substr(0, i);
	if (tmpProtocol != "HTTP" && tmpProtocol != "http")
		throw (badRequestNotHttp());

	// Parsing (HTTP-Version)
	i = firstString.length() - 1;
	size_t start = 0;
	while (std::isdigit(firstString[start]) == 0 && start < i)
		start++;
	if (start >= i)
		throw (badRequestHttpVersion());
	_httpVersion = atof(firstString.substr(start, i).c_str());
	firstString.erase(0, i);
}

void Request::parseKeyValue(std::string &header)
{
	size_t	start = 0;
	size_t	end;
	std::string	key;
	std::string value;

	if (header.empty() || header[0] == '\r')
		return ;

	// Extract key
	end = header.find_first_of(':');
	if (end == std::string::npos)
		throw (badRequestHeader());
	key = header.substr(start, end);

	// Extract value
	start = end + 1;
	while (header[start] == ' ' || header[start] == '\t')
		start++;
	value = header.substr(start, header.length());
	value.erase(value.find_last_not_of(" \n\r\t") + 1);
	// Add a new header to the map container
	_httpHeaders[key] = value;
}

void Request::parseHostName()
{
	std::map<std::string, std::string>::iterator it = _httpHeaders.find("Host");
	if (it != _httpHeaders.end())
		_hostName = it->second;
	else
		_hostName = "default";
	//std::cout << BLU << "Host name: " << _hostName << RES << std::endl;
}

void Request::parseBody(std::string &body)
{
	if (body.empty())
		return ;
	_requestBody = body.substr(0);
}

// Getters:
int Request::getMethod() const { return (this->_method); }
std::string const Request::getUri() const { return (this->_uri); }
float Request::getVersion() const { return (this->_httpVersion); }
std::string const Request::getHostname() const { return (this->_hostName); }
std::string const Request::getRequestBody() const { return (this->_requestBody); }
std::map<std::string, std::string> const Request::getHttpHeaders() const { return (this->_httpHeaders); }


// For printing:
std::ostream & operator<< (std::ostream & ostr, Request const &req)
{
	ostr << GRN << "\nSTART OF REQUEST PARSING----------------------o" << RES << std::endl;
	ostr << GRN << "Method: " << RES;
	if (req.getMethod() == 0)
		ostr << "GET" << std::endl;
	else if (req.getMethod() == 1)
		ostr << "POST" << std::endl;
	else if (req.getMethod() == 2)
		ostr << "DELETE" << std::endl;
	else
		ostr << "UNKNOWN" << std::endl;

	ostr << GRN << "URI: " << RES << req.getUri() << std::endl;
	ostr << GRN << "HTTP version: " << RES << req.getVersion() << std::endl;
	ostr << GRN << "Host: " << RES << req.getHostname() << std::endl;
	ostr << GRN << "Headers: " << RES << std::endl;

	std::map<std::string, std::string> headers = req.getHttpHeaders();

	for (std::map<std::string, std::string>::iterator it = headers.begin(); it != headers.end(); it++)
		ostr << it->first << ": " << it->second << std::endl;

	ostr << GRN << "Request body:" << RES << req.getRequestBody() << std::endl;
	ostr << GRN << "END-------------------------------------------o\n" << RES << std::endl;
	return (ostr);
}