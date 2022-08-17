#ifndef TOOLS_HPP
# define TOOLS_HPP

# include "numeric_reply.hpp"
# include "Server.hpp"
# include "channel.hpp"
# include "user.hpp"
# include "cmds.hpp"
# include <iostream>
# include <map>
# include <sstream>
# include <iterator>

# define TIMEOUT 500

//in err_msg.cpp
int	numeric_reply(int err, user* usr, Server& srv);
int	numeric_reply(int err, channel* chan, Server& srv);
int	numeric_reply(int err, std::string s, Server& srv);//s for cmd, operation, charactere
int	numeric_reply(int err, Server& srv);
int	numeric_reply(int err, std::string s/*, file f*/, Server& srv);
int	numeric_reply(int err, user* usr, channel* chan, Server& srv);

//in params.cpp
std::vector<std::string>	params(std::string s);
std::vector<std::string>	paramsSeparedByComas(std::string txt);

//in handle_commands.cpp
void	make_full_command(std::map<unsigned int, std::string> &msg,
	std::map<unsigned int, std::string> &buffers,
	std::map<unsigned int, user *> &users,
	std::vector<channel *> &channels,
	Server &server);

//in timeout.cpp
void	timeout(std::map<unsigned int, user *> &users, Server &server);

//in utils.cpp

/**
* Description:
* 	Convert a T to string.
* 
* Args:
* 	val: The value to convert.
* 
* Return:
* 	The value converted to string.
* 
* Notes:
* 	Does it work with anything ?!
**/

template <typename T>
std::string to_string(T val)
{
	std::stringstream ss;
	ss << val;
	return ss.str();
}

#endif