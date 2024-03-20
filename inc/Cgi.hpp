/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:41:27 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 13:03:49 by tzanchi          ###   ########.fr       */
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

	void	print( void ) const;
	Cgi*	clone( void ) const;
};

#endif
