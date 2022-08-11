#include "numeric_reply.hpp"
// #include "server.hpp"
#include "channel.hpp"
#include "user.hpp"

//in err_msg.cpp
int	error_msg(int err, user* usr, server* srv);
int	error_msg(int err, channel* chan, server* srv);
int	error_msg(int err, std::string s, server* srv);//s for cmd, operation, charactere
int	error_msg(int err, server* srv);
int	error_msg(int err, std::string s/*, file f*/, server* srv);
int	error_msg(int err, user* usr, channel* chan, server* srv);

//in params.cpp
std::vector<std::string>	params(std::string s);