#include "OpCodes.hpp"
#include "OpCodesEnum.h"
#include "SendPacket.h"

#include "SLoginArbiter.h"
#include "SCheckVersion.h"
#include "SSetVisibleRange.h"
#include "RGetPlayerList.h"
#include "RCanCreatePlayer.h"
#include "RStrEvaluateList.h"
#include "RCheckUsername.h"
#include "RCreatePlayer.h"
#include "RHardwareInfo.h"
#include "RReqVipSystemInfo.h"
#include "RSelectPlayer.h"
#include "RMovePlayer.h"
#include "RSavePlayerAccountSettings.h"
#include "RGetPlayerGuildLogo.h"
#include "RDeletePlayer.h"
#include "RChangeUserLobbySlotId.h"
#include "RCancelDeletePlayer.h"
#include "RLoadTopoFin.h"
#include "RTradeBrokerHighestItemLevel.h"
#include "RUnionSummary.h"
#include "RServerTime.h"
#include "RUpdateContentsPlayTime.h"
#include "RSimpleTipRepeatCheck.h"
#include "RSaveUserSettings.h"
#include "RRequestInstoreProductList.h"
#include "RGuardPkPolicy.h"
#include "RDungeonCoolTImeList.h"
#include "RRequestUserItemLevelInfo.h"
#include "RDungeonClearCountList.h"
#include "RNpcGuildList.h"
#include "RRaignInfo.h"
#include "RVisitNewSection.h"
#include "REventGuide.h"
#include "RShowInven.h"
#include "RSkillLearnRequest.h"
#include "RSkillLearnList.h"
#include "RStartSkill.h"
#include "RCancelSkill.h"
#include "RNotifyLocationInAction.h"
#include "RRequestGameStatPing.h"
#include "RExit.h"
#include "RChat.h"
#include "RReturnToLobby.h"
#include "RShowItemToolTipEx.h"
#include "RDelItem.h"
#include "RMoveItemPos.h"
#include "REquipItem.h"
#include "RRequestContract.h"
#include "RInventoryAutoSort.h"
#include "RUnequipItem.h"
#include "RTryLootDropItem.h"
#include "RUseItem.h"
#include "RSocial.h"


void OpCodes::Release()
{
	for (size_t i = 0; i < _opCodesList.size(); i++)
	{
		if (_opCodesList[i])
		{
			delete _opCodesList[i];
			_opCodesList[i] = 0;
		}
	}
	_opCodesList.clear();
}

const bool OpCodes::Initialize()
{
	Add(new RExit());
	Add(new SCheckVersion());
	Add(new SLoginArbiter());
	Add(new SSetVisibleRange());
	Add(new RGetPlayerList());
	Add(new RHardwareInfo());
	Add(new RReqVipSystemInfo());
	Add(new RCanCreatePlayer());
	Add(new RStrEvaluateList());
	Add(new RCheckUsername());
	Add(new RCreatePlayer());
	Add(new RSelectPlayer());
	Add(new RSavePlayerAccountSettings());
	Add(new RMovePlayer());
	Add(new RGetPlayerGuildLogo());
	Add(new RDeletePlayer());
	Add(new RChangeUserLobbySlotId());
	Add(new RCancelDeletePlayer());
	Add(new RLoadTopoFin());
	Add(new RTradeBrokerHighestItemLevel());
	Add(new RUnionSummary());
	Add(new RServerTime());
	Add(new RUpdateContentsPlayTime()); //todo
	Add(new RSimpleTipRepeatCheck());
	Add(new RSaveUserSettings());
	Add(new RRequestInstoreProductList()); //todo
	Add(new RGuardPkPolicy());
	Add(new RDungeonCoolTimeList());
	Add(new RRequestUserItemLevelInfo());
	Add(new RDungeonClearCountList());
	Add(new RNpcGuildList());
	Add(new RRaignInfo());
	Add(new RVisitNewSection());
	Add(new REventGuide());
	Add(new RShowInven());
	Add(new RSkillLearnRequest());
	Add(new RSkillLearnList()); //todo
	Add(new RStartSkill());
	Add(new RCancelSkill());
	Add(new RNotifyLocationInAction());
	Add(new RRequestGameStatPing());
	Add(new RChat());
	Add(new RReturnToLobby());
	Add(new RShowItemToolTipEx());
	Add(new REquipItem());
	Add(new RDelItem());
	Add(new RMoveItemPos());
	Add(new RRequestContract());
	Add(new RInventoryAutoSort());
	Add(new RUnequipItem());
	Add(new RTryLootDropItem());
	Add(new RUseItem());
	Add(new RSocial());

	return true;
}

const SendPacket const * OpCodes::Get(OpCode opCode)
{
	for (size_t i = 0; i < _opCodesList.size(); i++)
	{
		if (_opCodesList[i])
		{
			if (opCode == _opCodesList[i]->_toRecv)
			{
				return _opCodesList[i];
			}
		}
	}
	return nullptr;
}

bool OpCodes::Add(const SendPacket const  *sendPacket)
{
	if (!sendPacket)
		return false;
	_opCodesList.push_back(sendPacket);
	return true;
}

const unsigned int OpCodes::Count()
{
	return _opCodesList.size();
}

std::vector<const SendPacket const *> OpCodes::_opCodesList;
