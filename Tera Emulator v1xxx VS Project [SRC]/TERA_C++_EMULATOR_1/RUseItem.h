#pragma once
#include "SendPacket.h"
class RUseItem :
	public SendPacket
{
public:
	RUseItem();
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

