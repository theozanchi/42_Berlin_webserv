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
		_response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>LIBFT HACKERS</title>\n</head>\n<body>\n \
                        <h1>LIBFT HACKERS</h1>\n<p>listen on port 8080</p>\n</body>\n</html>\n";
	else
		_response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\n\n<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n<meta charset=\"utf-8\">\n<title>Error page</title>\n</head>\n<body>\n \
                        <h1>000</h1>\n<p>Erroe page</p>\n</body>\n</html>\n";
}

const char* Response::getResponse() const
{
	return (_response);
}

// Printing the class:
std::ostream & operator<<(std::ostream &ostr, Response const &response)
{
	(void)response;
	ostr << BLU << "\nSTART OF RESPONSE ----------------------------o" << RES << std::endl;
	ostr << BLU << "END-------------------------------------------o\n" << RES << std::endl;

	return (ostr);
}