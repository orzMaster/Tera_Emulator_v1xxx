#include "MessagingSystem.h"
#include "Client.hpp"
#include "OpCodesEnum.h"
#include "Stream.h"
#include "Player.hpp"
#include "BroadcastService.h"

MessagingSystem::MessagingSystem()
{
}


MessagingSystem::~MessagingSystem()
{
}

void MessagingSystem::SendSystemMessage(Client * client, std::string message)
{
	Stream s = Stream();

	s.WriteInt16(0);
	s.WriteInt16(S_SYSTEM_MESSAGE);
	s.WriteInt16(6);
	s.WriteString(message);

	s.WritePos(0);
	BroadcastSystem::Broadcast(client, &s, ME, 0);
}

void MessagingSystem::SendCustomSystemMessage(Client * client, std::string message)
{


}

void MessagingSystem::SendLootItem(Client * caller, int itemId, int stackCount)
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)return;
	std::stringstream ss;
	Stream s = Stream();
	s.WriteInt16(0);
	s.WriteInt16(S_SYSTEM_MESSAGE_LOOT_ITEM);
	short textOffset = s.NextPos();

	s.WriteInt32(itemId);
	s.WriteInt32(0);
	s.WriteInt32(stackCount);
	s.WriteInt32(0);
	s.WriteInt32(0);
	s.WriteInt32(0);
	s.WriteByte(0);
	s.WriteByte(0);
	s.WriteByte(0);
	s.WritePos(textOffset);

	std::string message = "@379"; message += '\v'; message += "UserName"; message += '\v';
	message += p->_name;  message += '\v'; message += "ItemAmount"; message += '\v'; message += std::to_string(stackCount);
	message += '\v'; message += "ItemName"; message += '\v'; message += "@item:"; message += std::to_string(itemId);
	s.WriteString(message);
	s.WritePos(0);

	caller->Send(&s);
}

