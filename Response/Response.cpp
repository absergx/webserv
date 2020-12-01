/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 02:03:04 by imicah            #+#    #+#             */
/*   Updated: 2020/11/27 18:16:26 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() : _body_size(0) { }
Response::Response(std::string& status_code) : _status_code(status_code), _body_size(0) { }
Response::~Response() = default;

void Response::set_status_code(const std::string& status_code) {
	_status_code = status_code;
}

void Response::add_header(const std::pair<std::string, std::string>& header) {
	_headers.insert(header);
}