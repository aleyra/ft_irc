#include "cmds.hpp"

void	quit(std::vector<std::string> params, user &askingOne,
	std::vector<channel*> &chan_vec, Server &server,
	std::map<unsigned int, user *>& users)
{
	std::string reason = (params.size() == 0) ? "" : params[0];
	for (std::vector<channel *>::iterator it = chan_vec.begin();
		it != chan_vec.end(); ++it)
	{
		std::map<unsigned int, int>& usr_list = (*it)->getUsr_list();
		if ((*it)->getUsr_list().count(askingOne.getId()))
			(*it)->send(server, ":" + askingOne.getNick() + "!" + askingOne.getHistory_nick().front()
				+ "@" + askingOne.getIp() + " " + "QUIT " + askingOne.getNick() + ": " + reason);
		if (usr_list.at(askingOne.getId()) <= CHAN_OP)
			(*it)->rm1toNbChanOp();
		askingOne.rmList_chan((*it));
		(*it)->rmUsr_list(&askingOne);
		channel* chan = *it;
		if (chan->get_nb_chan_op() == 0){
			for (std::map<unsigned int, int>::const_iterator it2 = usr_list.begin(); it2 != usr_list.end(); ++it2){
				if (chan->hasMode('m') && ((it2->second < CHAN_OP && it2->second >= VOICE_OK) || usr_list.size() == 1)){
					usr_list.at(it2->first) = CHAN_OP;
					chan->add1toNbChanOp();
				}
				else if (it2->second < CHAN_OP){
					usr_list.at(it2->first) = CHAN_OP;
					chan->add1toNbChanOp();
				}
				if (chan->get_nb_chan_op() == 1)
					break;
			}
		}
	}
	error(askingOne, server, "quit requested", users);

}

void	quit_server(user &askingOne, Server &server, std::string msg,
	std::map<unsigned int, user *>& users)
{
	if (!askingOne.getIsonline())
		return;
	
	server.send(":" + askingOne.getNick() + "!" + askingOne.getHistory_nick().front() +
		"@" + askingOne.getIp() + " " + "QUIT " + msg, askingOne.getId());
	server.disconnect(askingOne, users);
}

std::map<unsigned int, std::string>	Server::receive(std::map<unsigned int, user *> &users, std::vector<channel*> &chan_vec)
{
	char	buffer[4096];
	std::map<unsigned int, std::string>	m;

	for (std::map<unsigned int, int>::iterator it = _users.begin();
		it != _users.end(); ++it)
	{
		size_t valread = 0;
		int sd = it->second;
		if (FD_ISSET(sd, &this->readfds))
		{
			fcntl(sd, F_SETFL, O_NONBLOCK);
			valread = recv(sd, buffer, 4095, 0);
			if (valread > 0)
			{
				buffer[valread] = '\0';
				for (size_t i = 0; i < valread - 1; ++i){
					if ((int)buffer[i] < 0)
						memset(buffer, 0, valread);
				}
				m[it->first] = buffer;
			}
			else
			{
				close(sd);
				it->second = 0;
				users[it->first]->setIsonline(false);
				std::vector<std::string> tmp;
				tmp.push_back("");
				quit(tmp, *users[it->first], chan_vec, *this, users);
			}
		}
	}
	return (m);
}