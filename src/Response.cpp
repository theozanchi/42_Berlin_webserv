/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:20:41 by ole               #+#    #+#             */
/*   Updated: 2024/03/20 16:20:54 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() {}
Response::Response(const Response &copy) { *this = copy; }
Response & Response::operator=(const Response &copy)
{
	(void)copy;
	return (*this);
}
Response::~Response() {}

Response::Response(const Configuration &config, const Request &request) : _request(request), _config(config)
{
	if (_request.getMethod() == GET)
		this->checkBuildGetResponse();
	else if (_request.getMethod() == POST)
	{
		// POST METHOD HERE
		this->checkBuildPostResponse();
	}
	else if (_request.getMethod() == DELETE)
	{
		// POST METHOD HERE
		this->checkBuildDeleteResponse();
	}
	else
		_response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>Error page</title>\n</head>\n<body>\n<h1>000</h1>\n<p>Error page</p>\n</body>\n</html>\n";
}

void Response::checkBuildGetResponse()								//GET METHOOD
{
	// DO CHECKS HERE:

	// Reading from HTML-file:
	_response = this->readFromFile("./content/default_website/index.html");
}

void checkBuildPostResponse() 										// POST METHOD
{
	std::cout << RED << "POST METHOD to be implemented here" << RES << std::endl;
}

void checkBuildDeleteResponse()  									// DELETE METHOD
{
	std::cout << RED << "DELETE METHOD to be implemented here" << RES << std::endl;
}

std::string Response::readFromFile(std::string const & fileName)  	//NOT FINISHED////////////
{
	std::ifstream		ifs(fileName.c_str(), std::ifstream::in); //Open an input file;
	std::ostringstream	fileContent;
	std::ostringstream	response;
	std::string 		fileContentString;

	if (ifs)
	{
		std::cout << RED << "FILE OPEN" << std::endl;
		fileContent << ifs.rdbuf();
		response << "HTTP/1.1 200 OK\r\n";
		response << "Content-Length: " << fileContent.str().length() << "\r\n";
		response << "Content-Type: text/html\r\n";					//ADD A FUNCTOIN TO GET CONTENT_TYPE
		response << "\r\n";
		response << fileContent.str();
		ifs.close();
		fileContentString = response.str();
	}
	else
		throw (badResponse());										// REPLACE: SHOW ERROR PAGE

	return (fileContentString);
}

std::string const & Response::getResponse() const
{
	return (_response);
}

// Printing the class:
std::ostream & operator<<(std::ostream &ostr, Response const &response)
{
	(void)response;
	ostr << BLU << "\nSTART OF RESPONSE ----------------------------o" << RES << std::endl;
	ostr << BLU << "Response: '" << RES << response.getResponse() << BLU << "'" << RES << std::endl;
	ostr << BLU << "END-------------------------------------------o\n" << RES << std::endl;

	return (ostr);
}