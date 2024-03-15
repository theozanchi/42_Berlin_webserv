/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:41:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 12:32:43 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "ALocation.hpp"

class Cgi : public ALocation {
private:

public:
	Cgi();
	Cgi( const Cgi& src );
	Cgi& operator=( const Cgi& src );
	~Cgi();
};

#endif
