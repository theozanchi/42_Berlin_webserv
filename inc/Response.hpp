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

#include "Request.hpp"
#include "Configuration.hpp"

class Response
{
private:
	Request			_request;
	Configuration	_config;
	const char* 	_response;

	Response();
public:
	Response(const Configuration &config, const Request &request);
	Response(const Response &copy);
	Response & operator=(const Response &copy);
	~Response();

	const char* getResponse() const;
};

std::ostream & operator<<(std::ostream &ostr, Response const &response);