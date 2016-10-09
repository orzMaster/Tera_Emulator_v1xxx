#include "ContractManager.h"
#include "ContractService.h"
#include "Contract.h"
#include <stdarg.h>

ContractManager::ContractManager(Client * client, Server * server)
{
	_root = server;
	_owner = client;
}

ContractManager::~ContractManager()
{
	_root = nullptr;
	_owner = nullptr;


	ReqContract * pop = nullptr;
	while (_requestedContracts.try_pop(pop))
	{
		pop->contract = nullptr;
		delete pop;
		pop = nullptr;
	}
}

void ContractManager::Run(ServerTimer::ServerTime * time)
{
	ReqContract * pop = nullptr;
	while (_requestedContracts.try_pop(pop))
	{
		bool hasContract = false;
		for (size_t i = 0; i < _contracts.size(); i++)
			if ((*_contracts[i]) == pop)
			{
				hasContract = true;
				break;
			}
		if (hasContract)
		{
			pop->contract = nullptr;
			delete pop;
			pop = nullptr;
		}
		else
		{
			pop->Action(_owner); //do it once
			_contracts.push_back(pop);
		}
	}




}

const bool ContractManager::RequestContract(int unk1, int contract, int unk2, int unk3, int unk4, std::string unk5)
{
	const Contract const* contr = ContractService::GetContract((ContractType)contract);
	if (contr)
	{
		ReqContract * reqContr = new ReqContract;
		reqContr->unk1 = unk1;
		reqContr->unk2 = unk2;
		reqContr->unk3 = unk3;
		reqContr->unk4 = unk4;
		reqContr->unk5 = unk5;
		reqContr->contract = contr;
		_requestedContracts.push(reqContr);
		return true;
	}
	return false;
}

void ContractManager::ReqContract::Action(Client * c)const
{
	if (contract)
		contract->Action(c, unk1, unk2, unk3, unk4, unk5);
}

const bool ContractManager::ReqContract::operator==(ReqContract * c2)
{
	return contract == c2->contract;
}
