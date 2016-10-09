#pragma once
#include "SendPacket.h"
class RSocial :
	public SendPacket
{
public:
	RSocial();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller) const override;
};

