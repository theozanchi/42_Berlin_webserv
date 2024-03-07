/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ALocation.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:59:59 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 11:40:56 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALOCATION_HPP
# define ALOCATION_HPP

# include <vector>
# include <string>

using namespace std;

class ALocation {
private:
	string			_path;
	vector<string>	_allow;
	bool			_autoIndex;

public:
	ALocation();
	ALocation( const ALocation& src );
	ALocation& operator=( const ALocation& src );
	virtual ~ALocation() = 0;
};

#endif
