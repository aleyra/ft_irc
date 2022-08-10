#include "user.hpp"//en attendant un .hpp qui inclu user.hpp
#include <list>
#include <map>
#include "numeric_reply.hpp"
//srv.hostname = is the name of the server (as used in message prefixes).

int	who(std::string name, server* srv){
	user*				usr;
	std::list<channel*>	list_chan;
	if (name.empty()){
		std::list<std::map<int, class user> > usr_list;//a changer // recup la liste des user notee ici usr_list
		for (std::list<std::map<int, class user> >::iterator it = usr_list.begin();
				 it != usr_list.end(); ++it){
			usr = it->at;//?????

		}
	}
	else {
		usr = searchUser(name);
		if (usr == NULL){
			std::cout << "<client>" << " " << name <<" :End of WHO list" << std::endl;//RPl_ENDOFWHO//<client> a modifier
			return RPL_ENDOFWHO;
		}
		std::cout << "<client>" << " ";
		list_chan = usr->getList_chan();
		if (!list_chan.empty())
			std::cout << list_chan.begin()->getName();
		else 
			std::cout << "*";
		std::cout << " " << usr->getUsername();
		// std::cout << " " <<"<host>";//<host> a modifier //????qu'est-ce que le host ici ?
		std:: cout << " " << srv.hostname;//<server>
		std::cout << " " << usr->getNick() << " ";//<nick>//
		if (usr->getAway() == true)//<flags>
			std::cout << "G";//G for gone
		else
			std::cout << "H";//H for here
		if (usr->getLvl() == 2)
			std::cout <<"*";//means is en srv op
		for (std::list<channel>::iterator it = list_chan.begin();
				it != list_chan.end(); ++it){
			if (it->)
		}
		//:<hopcount> <realname> ;
	}

	
}

int	who(std::string name, char o, server* srv){
	if (o != 'o')
		return EXIT_FAILURE;//chercher dans la doc comment reagir dans le cas ou l'option o n'est pas la bonne
	
	user*	usr;
	if (name.empty()){
		std::list<std::map<int, class user> > usr_list;//a changer // recup la liste des user notee ici usr_list
		for (std::list<std::map<int, class user> >::iterator it = usr_list.begin(); it != usr_list.end(); it++){
			usr = it->at;//?????		
			if (usr->getIsop() == true){

			}
		}
	}

	return RPL_ENDOFWHO;
}