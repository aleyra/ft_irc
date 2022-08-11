#include "numeric_reply.hpp"
#include "Server.hpp"
#include "channel.hpp"
#include "user.hpp"

//in err_msg.cpp
int	error_msg(int err, user* usr, Server* srv);
int	error_msg(int err, channel* chan, Server* srv);
int	error_msg(int err, std::string s, Server* srv);//s for cmd, operation, charactere
int	error_msg(int err, Server* srv);
int	error_msg(int err, std::string s/*, file f*/, Server* srv);
int	error_msg(int err, user* usr, channel* chan, Server* srv);

//in params.cpp
std::vector<std::string>	params(std::string s);