/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:51:45 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 14:52:14 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDLOCATION_HPP
# define STDLOCATION_HPP

# include "ALocation.hpp"

class StdLocation : public ALocation {
private:
	string	_index;

public:
	StdLocation();
	StdLocation( const StdLocation& src );
	StdLocation& operator=( const StdLocation& src );
	~StdLocation();
};

#endif