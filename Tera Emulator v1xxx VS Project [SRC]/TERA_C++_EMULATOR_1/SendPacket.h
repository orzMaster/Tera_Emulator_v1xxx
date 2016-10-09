#ifndef SENDPAKCET_H
#define SENDPAKCET_H

#include "Stream.h"
#include "OpCodesEnum.h"

#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"

#include "BroadcastService.h"

#include <vector>
#include <sstream>

class Client; class Account; class Player;
class SendPacket
{
	friend class BroadcastSystem;
public:
	SendPacket(OpCode toRecv, bool ordered = true);
	virtual void Process(OpCode opCode, Stream * data, Client* caller) const = 0;
	OpCode _toRecv;
	bool _orderedPacket;
};

#endif