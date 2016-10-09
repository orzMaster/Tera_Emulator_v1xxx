#include "SCheckVersion.h"

SCheckVersion::SCheckVersion() : SendPacket(C_CHECK_VERSION)
{
}

void SCheckVersion::Process(OpCode opCode, Stream * data, Client * caller) const
{
	
}
