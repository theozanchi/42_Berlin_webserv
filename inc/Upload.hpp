/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Upload.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzanchi <tzanchi@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:46:25 by tzanchi           #+#    #+#             */
/*   Updated: 2024/03/27 16:19:12 by tzanchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPLOAD_HPP
# define UPLOAD_HPP

# include "ALocation.hpp"

class Upload : public ALocation{
private:
	string	_uploadStore;
	bool	_isUploadStoreSet;

public:
	Upload( const Server& server );
	Upload( const Upload& src );
	Upload& operator=( const Upload& src );
	~Upload();

	void	setUploadStore( const vector<string>& tokens );

	string	getUploadStore( void ) const;

	Upload*	clone( void ) const;
	void	print( void ) const;
	void	merge( Upload* src );
};

#endif
