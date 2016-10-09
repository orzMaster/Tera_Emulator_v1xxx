#include "RGetPlayerList.h"
#include "Client.hpp"
#include "Account.hpp"
#include "Player.hpp"
#include "PlayerService.h"
#include "ServerTimer.h"

RGetPlayerList::RGetPlayerList() : SendPacket(C_GET_USER_LIST)
{

}

void RGetPlayerList::Process(OpCode opCode, Stream * data, Client * caller)const
{
	Account * a = caller->GetAccount();
	if (a)
	{
		a->SendPlayerList(caller);
		a->SendAccountSettings(caller, false);
		a->SendAccountPackageList(caller, false);

		data->Clear();
		data->WriteInt16(17);
		data->WriteInt16(S_CONFIRM_INVITE_CODE_BUTTON);
		data->WriteInt32(15);
		data->WriteInt32(0);
		data->WriteInt32(0);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();

		data->WriteInt16(9);
		data->WriteInt16(S_UPDATE_CONTENTS_ON_OFF);
		data->WriteInt32(2);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();

		data->WriteInt16(9);
		data->WriteInt16(S_UPDATE_CONTENTS_ON_OFF);
		data->WriteInt32(3);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();

		data->WriteInt16(9);
		data->WriteInt16(S_UPDATE_CONTENTS_ON_OFF);
		data->WriteInt32(4);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();

		data->WriteInt16(9);
		data->WriteInt16(S_UPDATE_CONTENTS_ON_OFF);
		data->WriteInt32(8);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();

		data->WriteInt16(9);
		data->WriteInt16(S_UPDATE_CONTENTS_ON_OFF);
		data->WriteInt32(9);
		data->WriteByte(0);
		caller->Send(data);
		data->Clear();
	}
	else
		caller->Close();
}

//000000005D 01710120
//00910140 00D10101 50370000 00000005
//00000000 00000001 000000D7 0700001C
//05000001 00000019 000000D9 2309001E
//A4A05700 00000000 00000000 00000000
//E6545CA8 11270000 00000000 00000000
//9C3A0000 9D3A0000 9E3A0000 00000000
//00000000 00000000 00000000 00000000
//00000000 65000202 02010100 00000000
//00000000 00000000 0000E654 5CA80000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 0000A301
//00000100 00000000 01640000 00000000
//00000000 00000000 00000000 00540061
//00720074 00610072 0069006E 00610000
//00100408 0D000000 00101B1F 00101000
//001C0900 130C0A10 000D1F0C 09131000
//00011310 13131013 13130F0F 0F0F0F0F
//0F10130A 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00000000 00000000 00000000
//00000000 00












