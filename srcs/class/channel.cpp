#include "channel.hpp"
#include <list>

#pragma region constructors destructor
channel::channel(){}

channel::channel(channel const & src){*this = src;}

channel::channel(std::string name, user* founder){
	this->_name = name;
	this->_founder = founder;
	this->_isMod = false;
	this->_usr_list[founder] = 4;
}

channel::~channel(){
	this->_usr_list.clear();
}

#pragma endregion constructors destructor

#pragma region overload d operateurs
channel&	channel::operator=(channel const &src){
	this->_name = src._name;
	this->_founder = src._founder;
	this->_isMod = src._isMod;
	this->_usr_list = src._usr_list;
	return *this;
}

#pragma endregion overload d operateurs

#pragma region getters and setters
	void	channel::setName(std::string n){this->_name = n;}

	std::string const &	channel::getName() const{return this->_name;}

	user const &	channel::getFounder() const{return this->_founder;}

	void	channel::setIsMod(bool b){this->_isMod = b;}

	bool const &	channel::getIsMod() const{return this->_isMod;}

	std::map<user*, int> const &	channel::getUsr_list() const{
		return this->_usr_list;
	}

#pragma endregion getters and setters

#pragma region other member functions
	void	channel::addUsr_list(user* nu){this->_usr_list[nu] = 0;}

	void	channel::rmUsr_list(user* u){
		std::list<user*>::iterator f = std::find(this->_usr_list.begin(),
			this->_usr_list.end(), u);
		if (f == this->_usr_list.end())
			this->_usr_list.erase(nu);
	}

#pragma endregion other member functions