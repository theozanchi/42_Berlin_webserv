/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:59 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/20 17:12:04 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALOCATION_HPP
# define ALOCATION_HPP

# include <vector>
# include <string>

using namespace std;

class ALocation {
protected:
	string			_path;
	vector<string>	_allow;
	bool			_autoIndex;

public:
	ALocation();
	ALocation( const ALocation& src );
	ALocation& operator=( const ALocation& src );
	virtual ~ALocation() = 0;

	void				setPath( const vector<string>& tokens );
	void				setAllow( const vector<string>& tokens );
	void				setAutoIndex( const vector<string>& tokens );

	string				getPath( void ) const;
	string				getAllow( size_t idx ) const;
	vector<string>		getAllow( void ) const;
	bool				isAllow( const string& method ) const;
	bool				getAutoIndex( void ) const;

	virtual void		print( void ) const = 0;
	virtual ALocation*	clone( void ) const = 0;
};

#endif
