#include "cmds.hpp"

int	list(std::string params, std::vector<channel*>& chan_vec, Server& srv){
	if (params.empty()){
		for (size_t i = 0; i < chan_vec.size(); ++i){
			numeric_reply(RPL_LIST, chan_vec[i], srv);
		}
	}
	std::vector<std::string>	v = paramsSeparedByComas(params);
	for (size_t i = 0; i < v.size(); ++i){
		numeric_reply(RPL_LIST, v[i], srv);
	}
	return (numeric_reply(RPL_LISTEND, srv));
}

