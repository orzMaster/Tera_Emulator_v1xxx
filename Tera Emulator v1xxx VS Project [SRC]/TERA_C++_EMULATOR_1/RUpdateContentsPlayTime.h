#pragma once
#include "SendPacket.h"
class RUpdateContentsPlayTime :
	public SendPacket
{
public:
	RUpdateContentsPlayTime();

	// Inherited via SendPacket
	virtual void Process(OpCode opCode, Stream * data, Client * caller)const override;
};

