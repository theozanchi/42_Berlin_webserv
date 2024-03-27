/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   StdLocation.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:51:45 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/27 16:18:02 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STDLOCATION_HPP
# define STDLOCATION_HPP

# include "ALocation.hpp"

class StdLocation : public ALocation {
private:
	string	_index;
	bool	_isIndexSet;

	bool	isValidIndex( const string& token );

public:
	StdLocation( const Server& server );
	StdLocation( const StdLocation& src );
	StdLocation& operator=( const StdLocation& src );
	~StdLocation();

	void			setIndex( const vector<string>& tokens );

	string			getIndex( void ) const;

	void			print( void ) const;
	StdLocation*	clone( void ) const;
	void			merge( StdLocation* src );
};

#endif
