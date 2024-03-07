/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:41:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 14:48:59 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "ALocation.hpp"

class CGI : public ALocation {
private:

public:
	CGI();
	CGI( const CGI& src );
	CGI& operator=( const CGI& src );
	~CGI() {}
};

#endif
