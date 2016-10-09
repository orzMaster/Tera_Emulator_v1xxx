#include "BindContract.h"
#include "Client.hpp"
#include "Player.hpp"

BindContract::BindContract() : Contract(BIND_CONTRACT)
{
}

void BindContract::Action(Client * caller, int unk1, int unk2, int unk3, int unk4, std::string unk5) const
{
	Player* p = caller->GetSelectedPlayer();
		if (!p)
			return;

	data->WriteInt16(8);
	data->WriteInt16(S_REPLY_REQUEST_CONTRACT);
	data->WriteInt32(_type);
	caller->Send(data);
	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_REQUEST_CONTRACT);
	short namePos = data->NextPos();
	short unkPos = data->NextPos();
	short unkPos2 = data->NextPos();
	data->WriteInt16(17); //unk [size]?

	data->WriteInt32(p->_entityId);
	data->WriteInt32(p->_subId);

	data->WriteInt64(0); //unk
	data->WriteInt32(_type);
	data->WriteInt64(0); // unk [729734]
	data->WriteInt32(0);

	data->WritePos(namePos);
	data->WriteString(p->_name);

	data->WritePos(unkPos);
	data->WriteInt16(0);
	data->WritePos(unkPos2);
	data->WriteByte(0);
	data->WriteInt32(11);
	data->WriteInt64(0);
	data->WriteInt32(0);

	data->WritePos(0);
	caller->Send(data);
	data->Clear();

}