/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ole <ole@student.42berlin.de>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:20:23 by ole               #+#    #+#             */
/*   Updated: 2024/03/20 16:20:34 by ole              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <fstream>
# include <iostream>

#include "Request.hpp"
#include "Configuration.hpp"

class Response
{
private:
	Request			_request;
	Configuration	_config;
	std::string 	_response;
	Response();

public:
	Response(const Configuration &config, const Request &request);
	Response(const Response &copy);
	Response & operator=(const Response &copy);
	~Response();

	void checkBuildGetResponse();  // GET METHOD
	void checkBuildPostResponse(); // POST METHOD
	void checkBuildDeleteResponse();   // DELETE METHOD

	std::string readFromFile(std::string const & fileName);

	std::string const & getResponse() const;

	class badResponse : public std::exception
	{
	public:
		virtual const char* what() const throw()
		{
			return ("Bad response");
		}
	};
};

std::ostream & operator<<(std::ostream &ostr, Response const &response);