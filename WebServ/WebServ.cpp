/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 19:48:56 by nikita            #+#    #+#             */
/*   Updated: 2020/11/22 14:20:45 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"

WebServ::WebServ(const std::vector<VirtualServer>& list_virtual_servers) : _list_virtual_servers(list_virtual_servers) { }

WebServ::~WebServ() {

}

std::map<std::string, std::string> WebServ::_check_request_header() {
	return (std::map<std::string, std::string>());
}

void WebServ::_execute_cgi_client() {

}

void WebServ::_parse_request_body() {

}

void WebServ::_get_request(VirtualServer&) {

}

void WebServ::_give_response() {

}

void WebServ::run_server() {

}

void WebServ::serve_client(int client_socket) {

}