#include "Contract.h"

Contract::Contract(ContractType type): _type(type)
{
	data = new Stream();
}

Contract::~Contract()
{
	if (data)
	{
		delete data;
		data = nullptr;
	}
}
