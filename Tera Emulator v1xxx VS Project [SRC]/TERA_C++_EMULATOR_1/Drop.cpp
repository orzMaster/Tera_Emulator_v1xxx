#include "Drop.h"



Drop::Drop() : DropEntity()
{
	_itemId = _stackCount = _expire = _mobEntityid = _unk1 = _unk2 = _unk4 = _unk5 = 0;
	_unk3 = 0;
	X = Y = Z = 0.0f;
}

Drop::Drop(int itemId, float x, float y, float z, int stackCount, unsigned char expire, int mobEntityid) : DropEntity()
{
	_itemId = itemId;
	X = x; Y = y; Z = z;
	_stackCount = stackCount;
	_expire = expire;
	_mobEntityid = mobEntityid;
	_slotInfo = nullptr;
	_hasSlotInfo = 0;
}


Drop::~Drop()
{
	_ownersEntityIds.clear();
	if (_slotInfo)
	{
		delete _slotInfo;
		_slotInfo = nullptr;
	}
}

void Drop::AddOwner(int entityId)
{
	bool contains = false;
	for (size_t i = 0; i < _ownersEntityIds.size(); i++)
	{
		if (_ownersEntityIds[i] == entityId)
		{
			contains = true;
			break;
		}
	}
	if (!contains)
	{
		_ownersEntityIds.push_back(entityId);
	}
}

const bool Drop::IsOwner(int entityId)
{
	if (_ownersEntityIds.size() == 0)
		return true;

	for (size_t i = 0; i < _ownersEntityIds.size(); i++)
	{
		if (_ownersEntityIds[i] == entityId)
			return true;
	}
	return false;
}
