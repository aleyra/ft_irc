#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <list>
#include <ctime>
#include <map>
#include "user.hpp"

class user;

class channel{
	private:
		std::string				_name;
		user*					_founder;
		bool					_isMod;//true si le chan est en mode moderate
		std::map<user*, int>	_usr_list;//value de map = lvl acces. 0 = default, 1 = voice ok, 2 = halfop, 3 = protected, 4 = chan op
		char					_mode;//https://datatracker.ietf.org/doc/html/rfc2811#section-4
		std::string				_topic;

	//#pragma region constructors destructor
	private:
		channel();
		channel(channel const & src);
	public:
		channel(std::string name, user* founder);
		~channel();
	//#pragma region constructors destructor

	// #pragma region overload d operateurs
	private:
		channel&	operator=(channel const &src);//merci de mettre a jour cette fct quand vous ajoutez des attributs
	// #pragma endregion overload d operateurs

	// #pragma region getters and setters
	public:
		void							setName(std::string n);
		std::string const &				getName() const;
		//pas de setter pour founder
		user *							getFounder() const;
		void							setIsMod(bool b);
		bool const &					getIsMod() const;
		//pas de setter pour _usr_list, voir addUsr_list et rmUsr_list
		std::map<user*, int> &			getUsr_list() ;
		void							setMode(char c);
		char const &					getMode() const;
		void							setTopic(std::string t);
		std::string	const &				getTopic() const;

	// #pragma endregion getters and setters

	// #pragma region other member functions
		void	addUsr_list(user* nu);
		void	rmUsr_list(user* u);
		void	change_lvl_usr(user* u, int lvl);
	// #pragma endregion other member functions
};

channel*	searchChannelByName(std::string mask, std::vector<channel*>& chan_vec);
int			countVisibleUsers(channel* chan);