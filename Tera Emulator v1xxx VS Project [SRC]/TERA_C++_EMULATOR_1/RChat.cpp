#include "RChat.h"

#include "ChatEnum.h"

RChat::RChat() : SendPacket(C_CHAT)
{
}


RChat::~RChat()
{
}

void RChat::Process(OpCode opCode, Stream * data, Client * caller)
{
	short nameOffset = data->ReadInt16();
	ChatType type = (ChatType)data->ReadInt16();

	data->_pos = nameOffset - 4;
	std::string text = data->ReadReceivedString();
	std::string message = "";
	if (text.size() > 12)
		for (size_t i = 6; i < text.size() - 7; i++)
		{
			message += text[i];
		}
	if (message != "")
	{
		if (ServerUtils::StringStartsWith(message, "./spawn"))
		{
			if (message.size() > 8)
			{
				int mobId = 0;
				sscanf_s(message.c_str(), "./spawn %d", &mobId);
				std::cout << ">>SPAWNED MobId[" << mobId << "]\n";
			}
			else
			{
				//todo send back notice [with ./spawn form]
			}

			return;
		}
		else if (ServerUtils::StringStartsWith(message, "./spme"))
		{
#pragma region SPAWN_ME

			Player * p = caller->_account->_selectedPlayer;
			data->Clear();
			data->WriteInt16(0);
			data->WriteInt16(S_SPAWN_USER);

			data->WriteInt64(0);



			short namePos = data->NextPos();
			short guildNamePos = data->NextPos();
			short Title = data->NextPos();

			short details1Pos = data->NextPos();
			data->WriteInt16(32);

			short gTitlePos = data->NextPos();
			short gTitleIconPos = data->NextPos();

			short details2Pos = data->NextPos();
			data->WriteInt16(64);

			data->WriteInt64(caller->_account->_selectedPlayer->_entityId + 1);
			data->WriteInt64(caller->_entityId + 1);

			data->WriteFloat(p->_position->_X + 10);
			data->WriteFloat(p->_position->_Y + 10);
			data->WriteFloat(p->_position->_Z + 10);
			data->WriteInt16(p->_position->_heading);

			data->WriteInt32(0); //relation ?? enemy / party member ...
			data->WriteInt32(p->_model);
			data->WriteInt16(0); //allawys 0?
			data->WriteInt16(0); //unk2
			data->WriteInt16(0); //unk3
			data->WriteInt16(0); //unk4 allways 0?
			data->WriteInt16(0); //unk5 0-3 ?

			data->WriteByte(1);
			data->WriteByte(1); //alive

			data->Write(p->_data, 8);

			data->WriteInt32(p->_playerWarehouse->weapon);
			data->WriteInt32(p->_playerWarehouse->armor);
			data->WriteInt32(p->_playerWarehouse->gloves);
			data->WriteInt32(p->_playerWarehouse->boots);
			data->WriteInt32(p->_playerWarehouse->innerWare);
			data->WriteInt32(p->_playerWarehouse->skin1);
			data->WriteInt32(p->_playerWarehouse->skin2);

			data->WriteInt32(0); //unk 0-1-3 ??
			data->WriteInt32(0); //mount...
			data->WriteInt32(7); //7 ???
			data->WriteInt32(0); // Title id



			data->WriteInt64(0);

			data->WriteInt64(0);
			data->WriteInt64(0);

			data->WriteInt64(0);
			data->WriteInt64(0);

			data->WriteInt64(0);
			data->WriteInt64(0);

			data->WriteInt32(0);	  //unk s
			data->WriteInt16(0);
			data->WriteByte(0); //allaways 0?

			data->WriteByte(13);		  //enchants ??
			data->WriteByte(0);		  //enchants ??
			data->WriteByte(0);		  //enchants ??
			data->WriteByte(0);		  //enchants ??

			data->WriteByte(0);
			data->WriteByte(0);

			data->WriteInt16(p->_level);

			data->WriteInt16(0);   //always 0?
			data->WriteInt32(0);   //always 0?
			data->WriteInt32(0);
			data->WriteByte(1); //unk boolean?

			data->WriteInt32(0);	//skins ?
			data->WriteInt32(0);	//skins ?
			data->WriteInt32(0);	//skins ?
			data->WriteInt32(0);	//skins ?
			data->WriteInt32(0);	//skins ?
			data->WriteInt32(0); //costumeDye # ?

			data->WriteInt32(0);
			data->WriteInt32(0);

			data->WriteByte(1); //boolean?

			data->WriteInt32(1);
			data->WriteInt32(0);
			data->WriteInt32(0);
			data->WriteInt32(0);
			data->WriteInt32(0);

			data->WriteByte(1); //boolean?
			data->WriteInt32(0);

			data->WriteFloat(1.0f); //allways 1.0f?

			data->WritePos(namePos);
			data->WriteString(p->_name);

			data->WritePos(guildNamePos);
			data->WriteInt16(0);
			data->WritePos(Title);
			data->WriteInt16(0);

			data->WritePos(details1Pos);
			data->Write(p->_details1, 32);


			data->WritePos(gTitlePos);
			data->WriteInt16(0);
			data->WritePos(gTitleIconPos);
			data->WriteInt16(0);

			data->WritePos(details2Pos);
			data->Write(p->_details2, 64);

			data->WritePos(0); //size
			caller->Send(data);
			data->Clear();
#pragma endregion
		}
		else if(ServerUtils::StringStartsWith(message, "./exit"))
		{
			std::cout << ">>CLIENT DISCONNECT REQUEST\n";
			data->Clear();
			caller->Close();
			return;
		}
		
	}



	data->Clear();

	data->WriteInt16(0);
	data->WriteInt16(S_CHAT);
	short namePos = data->NextPos();
	short textPos = data->NextPos();

	data->WriteInt32(ChatType::ADMIN_CHAT);

	data->WriteInt32(caller->_entityId);
	data->WriteInt32(caller->_account->_selectedPlayer->_entityId);

	data->WriteByte(1); //chat icon...
	data->WriteByte(1); //?
	data->WriteByte(5);
	data->WritePos(namePos);
	data->WriteString(text);
	data->WritePos(textPos);
	data->WriteString(caller->_account->_selectedPlayer->_name);

	data->WritePos(0);

	caller->Send(data);
	BroadcastSystem::Broadcast(caller, data, VISIBLE_CLIENTS, 0);
}
