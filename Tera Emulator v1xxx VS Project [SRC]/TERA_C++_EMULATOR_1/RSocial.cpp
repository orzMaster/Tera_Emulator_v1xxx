#include "RSocial.h"



RSocial::RSocial() : SendPacket(C_SOCIAL)
{
}

void RSocial::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Player* p = caller->GetSelectedPlayer();
	if (!p)
		return;

	int emote = data->ReadInt32();
	data->Clear();


	data->WriteInt16(21);
	data->WriteInt16(S_SOCIAL);
	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);
	data->WriteInt32(emote);
	data->WriteInt32(0);
	data->WriteByte(0);
	caller->Send(data);
	caller->SendToVisibleClients(data);
}