/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:29:23 by nikita            #+#    #+#             */
/*   Updated: 2020/11/26 12:39:53 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_LOCATION_HPP
# define WEBSERV_LOCATION_HPP

# define NUMBER_METHODS		6

# include <vector>
# include <string>
# include <cstdint>

enum {
	accepted = true,
	non_accepted = false
};

enum {
	GET,
	HEAD,
	POST,
	PUT,
	DELETE,
	OPTIONS,
};

enum {
	_default,
	cgi,
	proxy
};

class	Location {
private:
	std::vector<bool>	_allow_methods;
	std::string			_path;
	std::string			_root;
	std::string			_cgi_pass;
	std::string			_proxy_pass;
	bool				_autoindex;
	std::string			_if_request_is_directory;
	int 				_location_type;

public:
	Location();
	~Location() = default;

	void									set_location_type(int location_type);

	void									set_root(const std::string&);
	void									set_if_request_is_directory(const std::string&);


	void									set_cgi_path(const std::string&);
	void									set_autoindex(bool);

	void									add_accepted_method(uint8_t);

	[[nodiscard]] const	std::vector<bool>&	get_allow_methods() const;
	[[nodiscard]] int						get_location_type() const;
	[[nodiscard]] const std::string&		get_path() const;
	[[nodiscard]] const	std::string&		get_root() const;

	[[nodiscard]] bool						is_allow_method(const std::string&) const;
	[[nodiscard]] bool						is_autoindex() const;
};

#endif //WEBSERV_LOCATION_HPP