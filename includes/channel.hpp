#pragma once

# include "iostream"
# include "string"
# include "algorithm"
# include "list"
# include "ctime"
#include "user.hpp"

class channel{
	private:
		std::string			_name;
		user*				_founder;
		std::list<user*>	_usr_protected;//liste de usr qui ne peuvent etre kick, cette list ne peut etre modifiee par de simples "usr protected"
		std::list<user*>	_usr_op;//liste des usr op du chan
		std::list<user*>	_usr_halfop;//
		bool				_isMod;//true si le chan est en mode moderate
		std::list<user*>	_usr_list;

	#pragma region constructors destructor
	private:
		channel();
		channel(channel const & src);
	public:
		channel(std::string name, user* founder);
		~channel();
	#pragma region constructors destructor

	#pragma region overload d'operateurs
	private:
		channel&	operator=(channel const &src);//merci de mettre a jour cette fct quand vous ajoutez des attributs
	#pragma endregion overload d'operateurs
};