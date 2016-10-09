#pragma once
#include "DropEntity.h"
#include <vector>

class SLOT_INFO;
class Drop :
	public DropEntity
{
public:
	Drop();
	Drop(int itemId, float x = 0.0f, float y = 0.0f, float z = 0.0f, int stackCount = 1, unsigned char expire = 1, int mobEntityid = 0);
	~Drop();

	void AddOwner(int entityId);

	int
		_itemId,
		_stackCount,
		_mobEntityid,
		_unk1, _unk2, _unk4, _unk5;

	short
		_unk3;

	float
		X, Y, Z;

	unsigned char
		_expire,
		_hasSlotInfo;

	SLOT_INFO * _slotInfo;
	std::vector<int>  _ownersEntityIds;

	const bool IsOwner(int entityId);
};

