/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WebServ_parsing_request.cpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imicah <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 20:06:14 by imicah            #+#    #+#             */
/*   Updated: 2020/12/15 20:07:05 by imicah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WebServ.hpp"
#include <iostream>

std::string WebServ::methods[6] = {
		"GET",
		"HEAD",
		"POST",
		"PUT",
		"DELETE",
		"OPTIONS"
};

std::vector<std::string>	WebServ::_getArgs(const std::string &line) const {
	std::vector<std::string>	result;
	size_t						pos_find;

	std::string input(line);
	while (!input.empty()){
		pos_find = input.find(' ');
		input.erase(pos_find, input.find_first_not_of(' '));
		pos_find = input.find(' ');
		result.push_back(input.substr(0, pos_find));
		input.erase(0, pos_find);
	}
	return (result);
}

std::vector<std::string> WebServ::_trimRequest(std::string const& buff) const {
	std::vector<std::string> result;
	std::string::size_type start = 0;
	std::string::size_type pos = 0;
	while (true) {
		pos = buff.find("\r\n", start);
		result.push_back(buff.substr(start, pos - start));
		if (!buff.compare(pos, 4, "\r\n\r\n"))
			break ;
		start = pos + 2;
	}
	return result;
}

bool	WebServ::_checkCountSpace(std::string const& line, int numSpaces) const { //TODO добавить в хедер
	int countSpace = 0;
	for (int i = 0; i < line.size(); ++i)
		if (line[i] == ' ')
			++countSpace;
	return countSpace == numSpaces;
}

bool	WebServ::_checkMethod(std::string method, int size) const { //TODO добавить в хедер
	for (int i = 0; i < size; ++i) {
		if (WebServ::methods[i] == method)
			return true;
	}
	return false;
}

void 	WebServ::_strToLower(std::string& str) const {
	for (int i = 0; i < str.size(); ++i)
		str[i] = std::tolower(str[i]);
}

void	WebServ::parsing_request(Client *client) {

	try {
		Request		request;
		bool 		takeHost = false;
		std::vector<std::string> args = _trimRequest(client->get_buffer());
		if (!_checkCountSpace(args[0], 2))
			throw ResponseException("400", "Bad Request", "400.html");
		else {
			std::vector<std::string> line = _getArgs(args[0]);
			if (line.size() != 3 || _checkMethod(args[0], 6) || line[2] != HTTP_VERSION)
				throw ResponseException("400", "Bad Request", "400.html");
			request.set_method(line[0]);
			request.set_target(line[1]);
			for (size_t i = 1; i < args.size(); ++i) {
				line = _getArgs(args[i]);
				_strToLower(line[0]);
				if (line.size() == 1 || line.size() > 2 || line[0].back() != ':')
					throw ResponseException("400", "Bad Request", "400.html");
				std::string key = line[0].substr(0, line[0].size() - 1);
				if (key == "host")
					takeHost = true;
				request.add_header(std::make_pair(key, line[1]));
			}
			if (!takeHost)
				throw ResponseException("400", "Bad Request", "400.html");
		}
		client->set_request(request);
		client->next_stage();
	}
	catch (ResponseException& response) {
		response.generate_response();
		client->set_response(response);
		client->set_stage(send_response_);
	}
}