/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:25 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/15 10:54:18 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOAD_HPP
# define UPLOAD_HPP

# include "ALocation.hpp"

class Upload : public ALocation{
private:
	string	_uploadStore;

public:
	Upload();
	Upload( const Upload& src );
	Upload& operator=( const Upload& src );
	~Upload();

	void	setUploadStore( const vector<string>& tokens );
};

#endif
