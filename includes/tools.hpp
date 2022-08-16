#include "numeric_reply.hpp"
#include "Server.hpp"
#include "channel.hpp"
#include "user.hpp"
#include <sstream>
#include <iterator>

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
void	handle_commands(std::map<int, std::string> &msg, std::map<int, std::string> &buffers);