#include "ContractService.h"
#include "Contract.h"

#include "EnchantContract.h"
#include "BindContract.h"


const bool ContractService::Initialize()
{
	AddContrct(new EnchantContract());
	AddContrct(new BindContract());

	return true;
}

void ContractService::AddContrct(const Contract const * con)
{
	if (!con)
		return;

	_contracts.push_back(con);
}

const Contract const * ContractService::GetContract(ContractType type)
{
	for (size_t i = 0; i < _contracts.size(); i++)
	{
		if (_contracts[i]->_type == type)
			return _contracts[i];
	}
	return nullptr;
}

unsigned int ContractService::GetCount()
{
	return _contracts.size();
}

void ContractService::Release()
{
	for (size_t i = 0; i < _contracts.size(); i++)
	{
		delete _contracts[i];
		_contracts[i] = nullptr;
	}
	_contracts.clear();
}

std::vector<const Contract const*>  ContractService::_contracts;