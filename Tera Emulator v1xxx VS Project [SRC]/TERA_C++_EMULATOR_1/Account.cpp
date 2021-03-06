#include "Account.hpp"
#include "Player.hpp"
#include "Client.hpp"
#include "Stream.h"
#include "OpCodesEnum.h"
#include "BroadcastService.h"
#include "Inventory.h"
#include "ItemEnum.h"
#include "ServerTimer.h"

Account::Account() : Entity()
{
	_isGm = false;
	_lasOnlineUtc = 0;
	_username = "";
	_password = "";
	_email = "";
	_owner = nullptr;
	_coins = 0;
	_lasPlayerSubId = 32768;
	_remainingPlayTime = 0;
	_selectedPlayer = 0;
	_accountSettings = 0;
	_accountSettingsSize = 0;
	_lastLobbyId = 0;
}

Account::~Account()
{
	for (size_t i = 0; i < _playerList.size(); i++)
	{
		if (_playerList[i])
		{
			delete _playerList[i];
			_playerList[i] = nullptr;
		}
	}
	_playerList.clear();

	if (_accountSettings)
	{
		delete[] _accountSettings;
		_accountSettings = nullptr;
	}

	_selectedPlayer = nullptr;
}

const unsigned int Account::GetPlayerCount() const
{
	return _playerList.size();
}

Player * Account::GetPlayer(int id)
{
	Player* out_player = nullptr;
	for (size_t i = 0; i < _playerList.size(); i++)
	{
		if (_playerList[i])
			if (_playerList[i]->_entityId == id)
			{
				out_player = _playerList[i];
				break;
			}
	}

	return out_player;
}

Player * Account::GetPlayerByLobbyId(int lobbyid)
{
	for (size_t i = 0; i < _playerList.size(); i++)
	{
		if (_playerList[i] && _playerList[i]->_lobbyId == lobbyid)
			return _playerList[i];
	}
	return nullptr;
}

Player * Account::GetSelectedPlayer()
{
	return _selectedPlayer;
}

Player* Account::SelectPlayer(int lobbyId)
{
	_selectedPlayer = GetPlayerByLobbyId(lobbyId);
	return _selectedPlayer;
}

void Account::SendPlayerList(Client * caller)
{
	Stream * stream = new Stream();

	stream->WriteInt16(0);
	stream->WriteInt16(S_GET_USER_LIST);
	stream->WriteInt16((short)caller->GetAccount()->GetPlayerCount());
	short next = stream->NextPos();
	stream->WriteByte(0);
	stream->WriteInt32(0);
	stream->WriteInt32(3); //unk ((int)MAX_PLAYERS_PER_ACCOUNT)

	stream->WriteInt32(1);	//unk 
	stream->WriteInt16(0);
	stream->WriteInt32(40);//unk


	stream->WriteInt32(0);
	stream->WriteInt32(24);	//unk

	for (size_t i = 0; i < _playerList.size(); i++)
	{
		Player * p = _playerList[i];
		Inventory* iv = p->_inventory;
		if (!p || p->_toDelete)
			continue;
		stream->WritePos(next);
		stream->WriteInt16(stream->_pos);
		next = stream->NextPos();
	
		stream->WriteInt32(0);

		short name_pos = stream->NextPos();
		short details1_pos = stream->NextPos();
		stream->WriteInt16(32);
		short details2_pos = stream->NextPos();
		stream->WriteInt16(64);
		short guild_name_pos = stream->NextPos();

		stream->WriteInt32(p->_lobbyId);

		stream->WriteInt32(p->_playerInfo->pGender);
		stream->WriteInt32(p->_playerInfo->pRace);
		stream->WriteInt32(p->_playerInfo->pClass);
		stream->WriteInt32(p->_stats._level);

		stream->WriteInt32(6);//unk map id1 ? 
		stream->WriteInt32(1231); //unk 1c050000 1308

		stream->WriteInt32(p->_position->_worldMapWorldId);
		stream->WriteInt32(p->_position->_worldMapGuardId);
		stream->WriteInt32(p->_position->_worldMapSectionId);

		stream->WriteInt64(p->_lastOnlineUTC); //unk
		stream->WriteByte(p->_banTimeUTC > 0 ? 1 : 0); //deleteion in progress
		stream->WriteInt64(p->_banTimeUTC); //time until character deletion


		stream->WriteInt32(0xA817EB64);

		stream->WriteInt32((*iv)[PROFILE_WEAPON]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_EARRING_L]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_EARRING_R]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_ARMOR]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_GLOVES]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_BOOTS]->_info->_itemId);

		stream->WriteInt32((*iv)[PROFILE_NECKLACE]->_info->_itemId); //unk

		stream->WriteInt32((*iv)[PROFILE_RING_L]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_RING_R]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_INNERWARE]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_MASK]->_info->_itemId); //head
		stream->WriteInt32((*iv)[PROFILE_HEAD_ADRONMENT]->_info->_itemId); //face

		stream->Write(p->_data, 8);

		stream->WriteByte(this->_isGm ? 1 : 0);//isgm

		stream->WriteInt64(0);
		stream->WriteInt32(0); //4
		stream->WriteByte(0); //2


		stream->WriteInt32(0xA817EB64); //unk0xA85C54e6
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);
		stream->WriteInt64(0);

		stream->WriteInt32((*iv)[PROFILE_SKIN_HEAD]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_SKIN_FACE]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_SKIN_BACK]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_SKIN_WEAPON]->_info->_itemId);
		stream->WriteInt32((*iv)[PROFILE_SKIN_BODY]->_info->_itemId);
		stream->WriteInt32(0);
		//stream->WriteInt32(0);
		//stream->WriteInt32(0);
		//stream->WriteInt32(0);
		//stream->WriteInt32(0);
		//stream->WriteInt32(0);

		//stream->WriteByte((*iv)[PROFILE_WEAPON]->_info->_enchantLevel);
		//stream->WriteByte((*iv)[PROFILE_ARMOR]->_info->_enchantLevel);
		//stream->WriteByte((*iv)[PROFILE_GLOVES]->_info->_enchantLevel);
		//stream->WriteByte((*iv)[PROFILE_BOOTS]->_info->_enchantLevel);

		stream->WriteInt32(0); 

		stream->WriteInt32(55311);
		stream->WriteInt32(55311);
		stream->WriteByte(1);
		stream->WriteInt32(0);
		stream->WriteByte(0);

		stream->WriteInt32(25601);
		stream->WriteByte(0);

		stream->WriteInt32(30); //achievements

		stream->WriteInt32(0);
		stream->WriteInt32(0);
		stream->WriteInt32(0);

		stream->WritePos(name_pos);
		stream->WriteString(p->_name);

		stream->WritePos(details1_pos);
		stream->Write(p->_details1, 32);

		stream->WritePos(details2_pos);
		stream->Write(p->_details2, 64);

		stream->WritePos(guild_name_pos);
		stream->WriteInt16(0);
		
	}
	stream->WritePos(0);
	std::ofstream listDump = std::ofstream("C://users//narcis//desktop//list.packet");
	listDump.write((char*)stream->_raw, stream->_size);
	listDump.close();

	caller->Send(stream);
	stream->Clear();

}

void Account::AddPlayer(Player * p)
{
	p->_subId = _lasPlayerSubId;
	_lasPlayerSubId++;

	_playerCount++;
	p->_lobbyId = _playerCount;


	_playerList.push_back(p);
}

const bool  Account::RemovePlayer(Player * p)
{
	for (size_t i = 0; i < _playerList.size(); i++)
	{
		if (_playerList[i] == p)
		{
			p = 0;
			delete _playerList[i];
			_playerList[i] = 0;

			_playerList.erase(_playerList.begin() + i);
			return true;
		}
	}
	return false;
}

void Account::Logout()
{
	_owner = nullptr;
	_selectedPlayer = nullptr;
	_lasOnlineUtc = ServerTimer::GetCurrentUTC();
}

void Account::SendAccountSettings(Client * caller, bool broadcast)
{
	Stream s = Stream();
	s.WriteInt16(0);
	s.WriteInt16(S_LOAD_CLIENT_ACCOUNT_SETTING);
	if (_accountSettings)
	{
		s.WriteInt16(8);
		s.WriteInt16(_accountSettingsSize);
		s.Write(_accountSettings, _accountSettingsSize);
	}
	else
	{
		s.WriteInt16(8);
		s.WriteInt16(0);
	}
	s.WritePos(0);
	if (broadcast)
	{
		BroadcastSystem::Broadcast(caller, &s, ME, 0);
	}
	else
	{
		caller->Send(&s);
	}
	s.Clear();
}

void Account::SendAccountPackageList(Client * caller, bool broadcast)
{
	Stream st = Stream();
	st.WriteInt16(8);
	st.WriteInt16(S_ACCOUNT_PACKAGE_LIST);
	st.WriteInt32(0);
	if (broadcast)
		BroadcastSystem::Broadcast(caller, &st, ME, 0);
	else
		caller->Send(&st);
}
