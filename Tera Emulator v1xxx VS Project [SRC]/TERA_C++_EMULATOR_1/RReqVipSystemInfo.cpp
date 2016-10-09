#include "RReqVipSystemInfo.h"
#include "Client.hpp"
#include "Account.hpp"
#include "PlayerService.h"


RReqVipSystemInfo::RReqVipSystemInfo() : SendPacket(C_REQUEST_VIP_SYSTEM_INFO) 
{
}

void RReqVipSystemInfo::Process(OpCode opCode, Stream * data, Client * caller) const
{
	PlayerService::SendVipSystemInfo(caller, false);
}


