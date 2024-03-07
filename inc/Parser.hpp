/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:42 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/07 17:11:13 by tzanchi          ###   ########.fr       */
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
	static const set<string>	_authorizedStdLocationKeys;
	static const set<string>	_authorizedUploadKeys;
	static const set<string>	_authorizedCGIKeys;

public:

	static void	printAuthorizedKeys( void );
};

#endif
