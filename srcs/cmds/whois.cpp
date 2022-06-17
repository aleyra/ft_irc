#include "Irc.hpp"


//usr.nick = nickname of user
//usr.true.name = ???
//srv.host =
//usr.chan[10] = il faut un tableau de channel dans lequel le usr est 
//usr.lvl = lvl access
//usr.idle_time = time since last activity in seconds
int WhoisCmd(/*list of params = usr.mask*/, irc srv){
	User tmp;
	if (/*list empty*/)
		return (numeric_reply(ERR_NONICKNAMEGIVEN));
	for(/*each param of WHOIS*/){
		tmp = srv.findUser(/*a param*/)//chercher un nickname correspondant dans la liste des user ONLINE
		if (tmp != NULL){//if there is display :
			std::cout << usr.nick << "@" << usr << srv.host << "*:" << usr.true_name << std::endl;//RPL_WHOISUSER
			std::cout << usr.nick << ":";//RPL_WHOISCHANNELS
			for (int i = 0; i < 10; i++) {
				if (i != 0 && usr.chan[i] != NULL)
					std::cout << " ";
				if (usr.chan[i] == NULL)//ce n'est pas un channel où est le usr
					i = 10;
				else{
					//if it's a moderated channel and usr is allowed to speak
						std::cout << "+";
					/*else*/ if (usr.lvl > 0)//est un operateur du chan???
						std::cout << "@" ;//a verif
					std::cout << usr.chan[i];
				}
			}
			sdt::cout << std::endl;
			std::cout << usr.nick << ": " << usr.idle_time << "seconds idle\n";//RPL_WHOISIDLE
			if (/*is an irc op*/)//RPL_WHOISOPERATOR
				std::cout << usr.nick << "is an IRC operator\n";
		}
		else
			numeric_reply(ERR_NOSUCHNICK, /*param de WHOIS*/);
	}
	return (EXIT_SUCCESS);
}