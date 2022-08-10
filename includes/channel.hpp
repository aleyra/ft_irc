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

	#pragma region getters and setters
	public:
		void						setName(std::string n);
		std::string const &			getName() const;
		//pas de setter pour _founder
		user const &				getFounder() const;
		//pas de setter pour _usr_protected, voir addUsr_protected et rmUsr_protected
		std::list<user*> const &	getUsr_protected() const;
		//pas de setter pour _usr_op, voir addUsr_op et rmUsr_op
		std::list<user*> const &	getUsr_op() const;
		//pas de setter pour _usr_halfop, voir addUsr_halfop et rmUsr_halfop
		std::list<user*> const &	getUsr_halfop() const;
		void						setIsMod(bool b);
		bool const &				getIsMod() const;
		//pas de setter pour _usr_list, voir addUsr_list et rmUsr_list
		std::list<user*> const &	getUsr_list() const;

	#pragma endregion getters and setters

	#pragma region other member functions
		void	addUsr_protected(user* nu);//le plus recent est a la fin
		void	addUsr_op(user* nu);//le plus recent est a la fin
		void	addUsr_halfop(user* nu);//le plus recent est a la fin
		void	addUsr_list(user* nu);//le plus recent est a la fin
		void	rmUsr_protected(user* u);
		void	rmUsr_op(user* u);
		void	rmUsr_halfop(user* u);
		void	rmUsr_list(user* u);
	#pragma endregion other member functions
};