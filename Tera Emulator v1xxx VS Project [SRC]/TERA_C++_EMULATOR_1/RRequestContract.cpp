#include "RRequestContract.h"



RRequestContract::RRequestContract() : SendPacket(C_REQUEST_CONTRACT)
{
}

void RRequestContract::Process(OpCode opCode, Stream * data, Client * caller) const
{
	short nameOffset = data->ReadInt16();
	int unk1 = data->ReadInt32();
	int contract = data->ReadInt32();
	int unk2 = data->ReadInt32();
	int unk3 = data->ReadInt32();
	int unk4 = data->ReadInt32();
	data->_pos = nameOffset;
	std::string contractorName = data->ReadUTF16StringBigEdianToASCII();

	caller->RequestContract(unk1, contract, unk2, unk3, unk4, contractorName);

	//data->Clear();
	//data->WriteInt16(8);
	//data->WriteInt16(S_REPLY_REQUEST_CONTRACT);
	//data->WriteInt32(contract);
	//caller->Send(data);
	//data->Clear();

	//if (contract == 34) //enchant
	//{
	//	Player* p = caller->GetSelectedPlayer();
	//	if (!p)
	//		return;
	//	
	//	data->WriteInt16(0);
	//	data->WriteInt16(S_REQUEST_CONTRACT);
	//	short namePos = data->NextPos();
	//	short unkPos = data->NextPos();
	//	short unkPos2 = data->NextPos();
	//	data->WriteInt16(17); //unk [size]?
	//
	//	data->WriteInt32(p->_entityId);
	//	data->WriteInt32(p->_subId);
	//
	//	data->WriteInt64(0); //unk
	//	data->WriteInt32(contract);
	//	data->WriteInt64(0); // unk [729734]
	//	data->WriteInt32(0);
	//	
	//	data->WritePos(namePos);
	//	data->WriteString(p->_name);
	//
	//	data->WritePos(unkPos);
	//	data->WriteInt16(0);
	//	data->WritePos(unkPos2);
	//	data->WriteByte(0);
	//	data->WriteInt32(11); 
	//	data->WriteInt64(0);
	//	data->WriteInt32(0);
	//
	//	data->WritePos(0);
	//	caller->Send(data);
	//	data->Clear();
	//}
}
