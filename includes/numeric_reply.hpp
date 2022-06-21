#ifndef NUM_RPL_H
# define NUM_RPL_H
# include <iostream>
# include "user.hpp"//en attendant un .hpp qui inclu user.hpp

typedef enum numeric_reply : int {//order by cmds which are order by abc.
//NB : every error-type comment is because it already listed upper in the list
//and numbers are corresponding to point 6 of doc fr
//for ADMIN
	ERR_NOSUCHSERVER = -402,
	RPL_ADMINME = 256,
	RPL_ADMINLOC1 = 257,
	RPL_ADMINLOC2 = 258,
	RPL_ADMINEMAIL = 259,
//for AWAY
	RPL_UNAWAY = 305,
	RPL_NOWAWAY = 306,
//for INFO
	// ERR_NOSUCHSERVER,
	RPL_INFO = 371,
	RPL_ENDOFINFO = 374,
//for INVITE
	ERR_NEEDMOREPARAMS = -461,
	ERR_NOSUCHNICK = -401,
	ERR_NOTONCHANNEL = -442,
	ERR_USERONCHANNEL = -443,
	ERR_CHANOPRIVSNEEDED = -482,
	RPL_INVITING = 341,
	RPL_AWAY = 301,
//for ISON
	RPL_ISON = 303,
	// ERR_NEEDMOREPARAMS, 
//for JOIN
	// ERR_NEEDMOREPARAMS, 
	ERR_BANNEDFROMCHAN = -474,
	ERR_INVITEONLYCHAN = -473,
	ERR_BADCHANNELKEY = -475,
	ERR_CHANNELISFULL = -471,
	ERR_BADCHANMASK,
	ERR_NOSUCHCHANNEL = -403,
	ERR_TOOMANYCHANNELS = -405,
	RPL_TOPIC = 332,
//for KICK
	// ERR_NEEDMOREPARAMS,
	// ERR_NOSUCHCHANNEL,
	// ERR_BADCHANMASK,
	// ERR_CHANOPRIVSNEEDED,
	// ERR_NOTONCHANNEL,
//for KILL
	ERR_NOPRIVILEGES = -481,
	// ERR_NEEDMOREPARAMS,
    // ERR_NOSUCHNICK,
	ERR_CANTKILLSERVER = -483,
//for LIST
	// ERR_NOSUCHSERVER,
	RPL_LISTSTART = 321,
	RPL_LIST = 322,
	RPL_LISTEND = 323,
//for MODE
	// ERR_NEEDMOREPARAMS,
	RPL_CHANNELMODEIS = 324,
	// ERR_CHANOPRIVSNEEDED,
	// ERR_NOSUCHNICK, 
	// ERR_NOTONCHANNEL,
	ERR_KEYSET = -467,
	RPL_BANLIST = 367,
	RPL_ENDOFBANLIST = 368,
	ERR_UNKNOWNMODE = -472,
	// ERR_NOSUCHCHANNEL,
	ERR_USERSDONTMATCH = -502,
	RPL_UMODEIS = 221,
	ERR_UMODEUNKNOWNFLAG = -501,
//for NAMES
	RPL_NAMREPLY = 353,
	RPL_ENDOFNAMES = 366,
//for NOTICE see PRIVMSG ?
//for NICK
	ERR_NONICKNAMEGIVEN = -431,
	ERR_NICKNAMEINUSE = -433, 
	ERR_NICKCOLLISION = -436,
	ERR_ERRONEUSNICKNAME = -432,
//for OPER
	// ERR_NEEDMOREPARAMS,
	ERR_NOOPERHOST = -491,
	RPL_YOUREOPER = 381,
//for PART
	// ERR_NEEDMOREPARAMS,
	// ERR_NOSUCHCHANNEL,
	// ERR_NOTONCHANNEL, 
//for PASS
	// ERR_NEEDMOREPARAMS,
	ERR_ALREADYREGISTRED = -462,
//for PING
	ERR_NOORIGIN = -409,
	// ERR_NOSUCHSERVER
//for PONG
	// ERR_NOORIGIN,
	// ERR_NOSUCHSERVER,
//for PRIVMSG and NOTICE ?
	ERR_NORECIPIENT = -411,
	ERR_NOTEXTTOSEND = -412,
	ERR_CANNOTSENDTOCHAN = -404,
	ERR_NOTOPLEVEL = -413,
	ERR_WILDTOPLEVEL = -414,
	ERR_TOOMANYTARGETS = -407,
	// ERR_NOSUCHNICK,
	// RPL_AWAY,
//for REHASH
	RPL_REHASHING = 382,
	// ERR_NOPRIVILEGES,
//for RESTART
	// ERR_NOPRIVILEGES,
//for STATS
	// ERR_NOSUCHSERVER,
	RPL_STATSLINKINFO = 211,
	RPL_STATSCOMMANDS = 212,
	RPL_STATSCLINE = 213,
	RPL_STATSNLINE = 214,
	RPL_STATSILINE = 215,
	RPL_STATSKLINE = 216,
	RPL_ENDOFSTATS = 219,
	RPL_STATSLLINE = 241,
	RPL_STATSUPTIME = 242,
	RPL_STATSOLINE = 243,
	RPL_STATSHLINE = 244,
	RPL_STATSQLINE,//not found in numeric replies' paraph in the doc
//SUMMON 
	// ERR_NORECIPIENT,
	ERR_FILEERROR = -424,
	ERR_NOLOGIN = -444,
	// ERR_NOSUCHSERVER,
	RPL_SUMMONING = 342,
	ERR_SUMMONDISABLED = -445,
//for TIME
	// ERR_NOSUCHSERVER,
	RPL_TIME = 391,
//for TOPIC
	// ERR_NEEDMOREPARAMS,
	// ERR_NOTONCHANNEL, 
	RPL_NOTOPIC = 331,
	// RPL_TOPIC,
	// ERR_CHANOPRIVSNEEDED,
//for USER
	// ERR_NEEDMOREPARAMS,
	// ERR_ALREADYREGISTRED,
//for USERHOST
	RPL_USERHOST = 302,
	// ERR_NEEDMOREPARAMS,
//for USERS
	// ERR_NOSUCHSERVER,
	// ERR_FILEERROR,
	RPL_USERSSTART = 392,
	RPL_USERS = 393,
	RPL_ENDOFUSERS = 394,
	RPL_NOUSERS = 395,
	ERR_USERSDISABLED = -446,
//for VERSIOM
	// ERR_NOSUCHSERVER,
	RPL_VERSION = 351,
//for WALLOPS
	// ERR_NEEDMOREPARAMS,
//for WHO
	// ERR_NOSUCHSERVER,
	RPL_WHOREPLY = 352,
	RPL_ENDOFWHO = 315,
//for WHOIS
	// ERR_NOSUCHSERVER,
	// ERR_NONICKNAMEGIVEN,
	RPL_WHOISUSER = 311,
	RPL_WHOISCHANNELS = 319,
	RPL_WHOISSERVER = 312,
	// RPL_AWAY,
	RPL_WHOISOPERATOR = 313,
	RPL_WHOISIDLE = 317,
	// ERR_NOSUCHNICK,
	RPL_ENDOFWHOIS = 318,
//for WHOWAS
	// ERR_NONICKNAMEGIVEN,
	ERR_WASNOSUCHNICK = -406,
	RPL_WHOWASUSER = 314,
	// RPL_WHOISSERVER,
	RPL_ENDOFWHOWAS = 369,
//other //found while coding error_msg
	ERR_UNKNOWNCOMMAND = -421,
	ERR_NOMOTD = -422,
	ERR_NOADMININFO = -423,
	ERR_USERNOTINCHANNEL = -441,
	ERR_NOLOGIN = -444,
	ERR_NOTREGISTERED = -451,
	ERR_NOPERMFORHOST = -463,
	ERR_PASSWDMISMATCH = -464,
	ERR_YOUREBANNEDCREEP = -465,
	RPL_NONE = 300,

};

class user;//a faire
class server;//a faire
class channel;//a faire
int	error_msg(int err, user usr);
int	error_msg(int err, server srv);
int	error_msg(int err, channel chan);
int	error_msg(int err, std::string s);//s for cmd, operation, charactere
int	error_msg(int err);
int	error_msg(int err, std::string s/*, file f*/);
int	error_msg(int err, user usr, channel chan);
// int	error_msg(int err, user usr, server srv);

#endif