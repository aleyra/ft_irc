#include "user.hpp"//en attendant un .hpp qui inclu user.hpp
#include "numeric_reply.hpp"
#include <cstdlib>

//srv->host =
//usr->chan[10] = il faut un tableau de channel dans lequel le usr est 
//usr->idle_time = time since last activity in seconds

std::vector<std::string>	whowasParam(std::string s){
	std::istringstream iss(s);
	std::vector<std::string> results(std::istream_iterator<std::string>{iss},
                                 std::istream_iterator<std::string>());
	return (results);
}

int whowas(std::vector<std::string> params, server* srv){
	if (params.empty())
		return (numeric_reply(ERR_NONICKNAMEGIVEN));

	//transform params to a string and eventually an int
	if (params.size() > 2)
		return (EXIT_FAILURE);
	std::string	mask = *(params[0]);
	int			count = 0;
	if (params.size() == 2)
		count = std::atoi(params[1].c_str());

	//from string to user*
	user*		usr = findUser(mask);//chercher un nickname correspondant dans la liste des user OFFLINE ou ONLINE old nick
	
	//if no such mask
	if (usr == NULL){
		numeric_reply(ERR_NOSUCHNICK, mask);
		return (EXIT_SUCCESS);
	}
	
	//else
	std::cout << usr->getNick() << "@" << usr << srv->host << "*:"
		<< usr->getTruename() << std::endl;//RPL_WHOISUSER
	std::cout << usr->getNick() << ":";//RPL_WHOISCHANNELS
	std::vector<channel*> &list_chan = usr->getList_chan;

	for (int i = 0; i < list_chan.size(); ++i){
		if (i == 0 && i != list_chan.size() - 1)
			std::cout << " ";
		if (list_chan[i]->getIsMod() == true && list_chan[i]./*ici*/)//if it's a moderated channel and usr is allowed to speak
			std::cout << "+";
		/*else*/ if (usr->getLvl() > 0)//est un operateur du chan???
			std::cout << "@" ;//a verif
		std::cout << list_chan[i].name;
		
	}
	std::endl;
	std::cout << usr->getNick() << ": " << usr->idle_time << "seconds idle"
		<< std::endl;//RPL_WHOISIDLE
	if (/*is an irc op*/)//RPL_WHOISOPERATOR
		std::cout << usr->getNick() << "is an IRC operator" << std::endl;
	//autre chose ?
	
	return (EXIT_SUCCESS);
}