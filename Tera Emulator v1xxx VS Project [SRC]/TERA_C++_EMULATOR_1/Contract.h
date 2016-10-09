#pragma once

#include "Stream.h"
#include "ContractEnum.h"
#include "OpCodesEnum.h"
#include <string>

class Client;
class Contract
{
	friend class ContractService;
public:
	Contract(ContractType type);
	virtual ~Contract();

	virtual void Action(Client * client, int unk1, int unk2, int unk3, int unk4, std::string unk5) const = 0;

protected:
		const ContractType _type;
		Stream * data;
};

