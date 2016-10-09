#pragma once
#include "Contract.h"
class BindContract :
	public Contract
{
public:
	BindContract();

	// Inherited via Contract
	virtual void Action(Client * client, int unk1, int unk2, int unk3, int unk4, std::string unk5) const override;
};

