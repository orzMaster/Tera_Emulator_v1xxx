#include "RCreatePlayer.h"
#include "Inventory.h"
#include "ItemEnum.h"
#include "StatsService.h"
#include "SkillService.h"

RCreatePlayer::RCreatePlayer() : SendPacket(C_CREATE_USER)
{
}

void RCreatePlayer::Process(OpCode opCode, Stream * stream, Client * caller)const
{
	Account * a = nullptr;
	if ((a = caller->GetAccount()) && a->GetPlayerCount() < MAX_PLAYERS_PER_ACCOUNT)
	{
		short nameOffset = stream->ReadInt16();
		short details1Offset = stream->ReadInt16();
		stream->ReadInt16();
		short details2Offset = stream->ReadInt16();
		stream->ReadInt16();

		short gender = stream->ReadInt32();
		short race = stream->ReadInt32();
		short pClass = stream->ReadInt32();


		byte * data = new byte[8];
		stream->Read(data, 8);

		stream->_pos = nameOffset;
		std::string name = stream->ReadUTF16StringBigEdianToASCII();

		byte* details1 = new byte[32];
		stream->_pos = details1Offset;
		stream->Read(details1, 32);

		byte* details2 = new byte[64];
		stream->_pos = details2Offset;
		stream->Read(details2, 64);

		Player * newPlayer = new Player();
		newPlayer->_newPlayer = true;
		newPlayer->_name = name;
		newPlayer->_stats._level = 1;
		newPlayer->_exp = 1;
		newPlayer->_restedExp = 0;
		newPlayer->_maxExp = LevelingService::GetLevelExperience(1);
		newPlayer->_lastOnlineUTC = ServerTimer::GetCurrentUTC();
		newPlayer->_creationTimeUTC = ServerTimer::GetCurrentUTC();
		newPlayer->_banTimeUTC = 0;

		newPlayer->_details1 = details1;
		newPlayer->_details2 = details2;
		newPlayer->_data = data;

		newPlayer->_playerInfo = new Player::PlayerInfo;
		newPlayer->_playerInfo->pClass = (PlayerClass)pClass;
		newPlayer->_playerInfo->pGender = (PlayerGender)gender;
		newPlayer->_playerInfo->pRace = (PlayerRace)race;

		newPlayer->_model = 10000;
		newPlayer->_model += (newPlayer->_playerInfo->pRace * 2 + 1 + newPlayer->_playerInfo->pGender) * 100;
		newPlayer->_model += newPlayer->_playerInfo->pClass + 1;

		a->AddPlayer(newPlayer);

		Inventory::GetStarterInventory(newPlayer);

		WorldSystem::NewPlayerPosition(newPlayer);

		StatsService::GetPlayerStartStats(newPlayer);

		SkillService::GetStarterSkillList(newPlayer);

		stream->Clear();
		stream->WriteInt16(5);
		stream->WriteInt16(S_CREATE_USER);
		stream->WriteByte(1);
		caller->Send(stream);
		stream->Clear();
		return;
	}
	stream->Clear();
	stream->WriteInt16(5);
	stream->WriteInt16(S_CREATE_USER);
	stream->WriteByte(0);
	caller->Send(stream);
	stream->Clear();
}
//94001363 28003400 20005400 40000100
//00000300 00000000 00006502 01090E00
//01010064 00000000 41006600 61007200
//61000000 03101003 0A000015 1A101000
//11031000 08100A10 0C171010 10161608
//15100B10 01131013 13101313 130F0F0F
//0F0F0F0F 10130A00 10101000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000