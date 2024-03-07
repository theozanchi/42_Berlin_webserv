/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 15:52:36 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <set>
# include <string>

using namespace std;

class Parser {
private:
	Parser() {}
	~Parser() {}

	static const set<string>	_authorizedKeys;
	
public:
	static void	printAuthorizedKeys( void );
};

#endif
