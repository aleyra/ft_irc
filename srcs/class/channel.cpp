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

channel::~channel(){
	this->_usr_protected.clear();
	this->_usr_op.clear();
	this->_usr_halfop.clear();
	this->_usr_list.clear();
}

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

#pragma region getters and setters
	void	channel::setName(std::string n){this->_name = n;}

	std::string const &	channel::getName() const{return this->_name;}

	user const &	channel::getFounder() const{return this->_founder;}

	std::list<user*> const &	channel::getUsr_protected() const{
		return this->_usr_protected;
	}

	std::list<user*> const &	channel::getUsr_op() const{return this->_usr_op;}

	std::list<user*> const &	channel::getUsr_halfop() const{
		return this->_usr_halfop;
	}

	void	channel::setIsMod(bool b){this->_isMod = b;}

	bool const &	channel::getIsMod() const{return this->_isMod;}

	std::list<user*> const &	channel::getUsr_list() const{
		return this->_usr_list;
	}

#pragma endregion getters and setters

#pragma region other member functions
	void	channel::addUsr_protected(user* nu){
		this->_usr_protected.push_back(nu);
	}

	void	channel::addUsr_op(user* nu){this->_usr_op.push_back(nu);}

	void	channel::addUsr_halfop(user* nu){this->_usr_halfop.push_back(nu);}

	void	channel::addUsr_list(user* nu){this->_usr_list.push_back(nu);}

	void	channel::rmUsr_protected(user* u){
		std::list<user*>::iterator f = std::find(this->_usr_protected.begin(),
			this->_usr_protected.end(), u);
		if (f == this->_usr_protected.end())
			this->_usr_protected.erase(f);
	}

	void	channel::rmUsr_op(user* u){
		std::list<user*>::iterator f = std::find(this->_usr_op.begin(),
			this->_usr_op.end(), u);
		if (f == this->_usr_op.end())
			this->_usr_op.erase(f);
	}

	void	channel::rmUsr_halfop(user* u){
		std::list<user*>::iterator f = std::find(this->_usr_protected.begin(),
			this->_usr_protected.end(), u);
		if (f == this->_usr_protected.end())
			this->_usr_protected.erase(f);
	}

	void	channel::rmUsr_list(user* u){
		std::list<user*>::iterator f = std::find(this->_usr_protected.begin(),
			this->_usr_protected.end(), u);
		if (f == this->_usr_protected.end())
			this->_usr_protected.erase(f);
	}

#pragma endregion other member functions