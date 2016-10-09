#pragma once
#include "ServerTimer.h"
#include "ContractEnum.h"

#include <vector>
#include <string>
#include <concurrent_queue.h>

class Client; class Server; class Contract;
class ContractManager
{
private:
	struct ReqContract
	{
		int unk1, unk2, unk3, unk4;
		std::string unk5;
		const Contract const* contract;
		void Action(Client * c) const;

		const bool operator == (ReqContract* c2);
	};
public:
	ContractManager(Client* client, Server* server);
	~ContractManager();

	void Run(ServerTimer::ServerTime * time);

	const bool RequestContract(int unk1, int contract, int unk2, int unk3, int unk4, std::string unk5);
	//const bool CancelContract(int contract);
private:
	concurrency::concurrent_queue<ReqContract*> _requestedContracts;
	std::vector<ReqContract*> _contracts;
	Server* _root;
	Client* _owner;
};

