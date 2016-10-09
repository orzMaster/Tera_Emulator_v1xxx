#include "SLoginArbiter.h"
#include "PlayerService.h"
#include "Account.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "ChatEnum.h"

SLoginArbiter::SLoginArbiter() :SendPacket(C_LOGIN_ARBITER)
{

}
void SLoginArbiter::Process(OpCode opCode, Stream * stream, Client * caller) const
{
	short nameOffset = stream->ReadInt16();
	short ticketOffset = stream->ReadInt16();
	short ticketBytesCount = stream->ReadInt16();

	int unk1 = stream->ReadInt32();
	byte unk2 = stream->ReadByte();
	int unk3 = stream->ReadInt32();
	int patchVersion = stream->ReadInt32();

	if (patchVersion != CLIENT_VERSION)
	{
		caller->Close();
		return;
	}
	caller->_clientVerision = patchVersion;

	byte* ticket = new byte[ticketBytesCount];
	stream->_pos = ticketOffset;
	stream->Read(ticket, ticketBytesCount);

	stream->_pos = nameOffset;
	std::string username = stream->ReadUTF16StringBigEdianToASCII();
	std::string password = std::string((char*)ticket, 32); 
	password += '\0';
	
	stream->Clear();
	stream->WriteInt16(5);
	stream->WriteInt16(S_CHECK_VERSION);
	stream->WriteByte(1);
	caller->Send(stream);
	stream->Clear();
	

	Account * a = nullptr;
	if (!(a = PlayerService::PerformAccountLogin(username.c_str(), password.c_str())))
	{
		caller->Close();
		return;
	}
	if (a->_owner)
	{
		Player * pp = nullptr;
		if ((pp = a->_owner->GetSelectedPlayer()))
		{
			stream->Clear();
			stream->WriteInt16(0);
			stream->WriteInt16(S_CHAT);

			short namePos = stream->NextPos();
			short textPos = stream->NextPos();

			stream->WriteInt32(MAIN_CHAT);
			stream->WriteInt32(a->_owner->GetSelectedPlayer()->_entityId);
			stream->WriteInt32(a->_owner->GetSelectedPlayer()->_subId);

			stream->WriteByte(0);
			stream->WriteByte(0);
			stream->WriteByte(0);

			stream->WritePos(namePos);
			stream->WriteString(pp->_name);

			stream->WritePos(textPos);
			stream->WriteString("<FONT size='18'>Someone tried to login on your account! You'll be disconnected!</FONT>");
			stream->WritePos(0);
			a->_owner->Send(stream);

			Sleep(1500);
			a->_owner->Close();
			caller->Close();
		}
		else
		{
			a->_owner->Close();
			caller->Close();
		}
		return;
	}


	caller->LoginClient(a);
	stream->Clear();
	stream->WriteInt16(5);
	stream->WriteInt16(S_LOADING_SCREEN_CONTROL_INFO);
	stream->WriteByte(0);
	caller->Send(stream);
	stream->Clear();

	stream->WriteInt16(12);
	stream->WriteInt16(S_REMAIN_PLAY_TIME);
	stream->WriteInt32(6);
	stream->WriteInt32(0);
	caller->Send(stream);
	stream->Clear();

	stream->WriteInt16(23);
	stream->WriteInt16(S_LOGIN_ARBITER);
	stream->WriteInt32(1);
	stream->WriteInt32(0);
	stream->WriteInt16(0);
	stream->WriteInt32(6);
	stream->WriteInt32(0);
	stream->WriteByte(0);
	caller->Send(stream);
	stream->Clear();

	stream->WriteInt16(0);
	stream->WriteInt32(S_LOGIN_ACCOUNT_INFO);
	stream->WriteInt16(14); // server name offset
	stream->WriteInt64(6650346); //??? SERVER_ID??
	stream->WriteString("PlanetMT");
	stream->WritePos(0);
	caller->Send(stream);
	stream->Clear();

	delete[] ticket;
	ticket = 0;
}