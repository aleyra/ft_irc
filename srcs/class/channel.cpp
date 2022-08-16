#include "channel.hpp"
#include <list>

// #pragma region constructors destructor
channel::channel(){}

channel::channel(channel const & src){*this = src;}

channel::channel(std::string name, user* founder){
	this->_name = name;
	this->_founder = founder;
	this->_isMod = false;
	this->_usr_list[founder->getId()] = CHAN_OP;
	this->_mode = 0;
}

channel::~channel(){
	this->_usr_list.clear();
}

// #pragma endregion constructors destructor

// #pragma region overload d operateurs
channel&	channel::operator=(channel const &src){
	this->_name = src._name;
	this->_founder = src._founder;
	this->_isMod = src._isMod;
	this->_usr_list = src._usr_list;
	this->_mode = src._mode;
	return *this;
}

// #pragma endregion overload d operateurs

// #pragma region getters and setters
	void	channel::setName(std::string n){this->_name = n;}

	std::string const &	channel::getName() const{return this->_name;}

	user *	channel::getFounder() const{return this->_founder;}

	void	channel::setIsMod(bool b){this->_isMod = b;}

	bool const &	channel::getIsMod() const{return this->_isMod;}

	std::map<unsigned int, int> &	channel::getUsr_list() {
		return this->_usr_list;
	}
	
	void	channel::setMode(char c){
		this->_mode = c;
	}

	char const &	channel::getMode() const{
		return this->_mode;
	}

	void	channel::setTopic(std::string t){
		this->_topic = t;
	}

	std::string	const &	channel::getTopic() const{
		return this->_topic;
	}


// #pragma endregion getters and setters

// #pragma region other member functions
	void	channel::addUsr_list(user* nu){this->_usr_list[nu->getId()] = 0;}

	void	channel::rmUsr_list(user* u){
		std::map<unsigned int, int>::iterator f = this->_usr_list.find(u->getId());
		if (f == this->_usr_list.end())
			this->_usr_list.erase(u->getId());
	}

// #pragma endregion other member functions

channel*	searchChannelByName(std::string mask, std::vector<channel*>& chan_vec){
	for (size_t i = 0; i < chan_vec.size(); ++i){
		if (chan_vec[i]->getName().compare(mask) == 0)
			return chan_vec[i];
	}
	return NULL;
}

int	countVisibleUsers(channel* chan, std::map<unsigned int, user *>& users){
	int						count = 0;
	std::map<unsigned int, int> &	usr_list = chan->getUsr_list();

	for (std::map<unsigned int, int>::iterator it = usr_list.begin(); it != usr_list.end(); ++it){
		if (searchUserByID(it->first, users)->getMode() != 'i')
			count++;
	}
	return count;
}