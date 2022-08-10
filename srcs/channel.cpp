#include "channel.hpp"
#include <list>

#pragma region constructors destructor
channel::channel(){}

channel::channel(channel const & src){*this = src}

channel::channel(std::string name, user* founder){
	this->_name = name;
	this->_founder = founder;
	this->_usr_op.push_back(founder);
	this->_isMod = false;
	this->_usr_list.push_back(founder);
}

channel::~channel(){}

#pragma endregion constructors destructor

#pragma region overload d'operateurs
channel&	channel::operator=(channel const &src){
	this->_name = src._name;
	this->_founder = src._founder;
	if (!this->_usr_protected.empty())
		this->_usr_protected.clear();
	for (std::list<user*>::iterator it = src._usr_protected.begin();
		it != src._usr_protected.end(); ++it){
		this->_usr_protected.push_back(*it);
	}
	if (!this->_usr_op.empty())
		this->_usr_op.clear();
	for (std::list<user*>::iterator it = src._usr_op.begin();
		it != src._usr_op.end(); ++it){
		this->_usr_op.push_back(*it);
	}
	if (!this->_usr_halfop.empty())
		this->_usr_halfop.clear();
	for (std::list<user*>::iterator it = src._usr_halfop.begin();
		it != src._usr_halfop.end(); ++it){
		this->_usr_halfop.push_back(*it);
	}
	this->_isMod = src._isMod;
	if (!this->_usr_list.empty())
		this->_usr_list.clear();
	for (std::list<user*>::iterator it = src._usr_list.begin();
		it != src._usr_list.end(); ++it){
		this->_usr_list.push_back(*it);
	}
}

#pragma endregion overload d'operateurs