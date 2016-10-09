#include "InventorySlot.h"
#include "IItem.h"


InventorySlot::InventorySlot(int id)
{
	_isEmpty = 1;
	_id = id;
	_info = new SLOT_INFO();
}
InventorySlot::~InventorySlot()
{
	if (_info)
	{
		_info->_item = 0;
		delete _info;
		_info = 0;
	}
}

const bool InventorySlot::ClearSlot()
{
	_info->Clear();
	_isEmpty = 1;
	return true;
}

const bool InventorySlot::IsProfileSlot()
{
	return _id > 0 && _id <= 20;
}

const bool InventorySlot::operator<<(IItem * item)
{
	if (!_info)
		return false;
	_info->_item = item;

	return true;
}

const bool InventorySlot::operator<<(SLOT_INFO * info)
{
	return false;
}

const bool InventorySlot::operator >> (InventorySlot * slot)
{
	if (!slot || slot->_info) //we put me info to you info[null]
		return false;
	slot->_info = _info;
	ClearSlot();
	return true;
}

const bool InventorySlot::operator^(InventorySlot * slot)
{
	if (!slot || !slot->_info || !_info || slot == this)
		return false;

	byte emptyTemp = _isEmpty;
	_isEmpty = slot->_isEmpty;
	slot->_isEmpty = emptyTemp;
	//switch emptyVar

	SLOT_INFO *  temp = slot->_info;
	slot->_info = _info;
	_info = temp;



	return true;
}

InventorySlot::operator int()
{
	if (_info && _info->_item)
		return _info->_item->_entityId;
	return 0;
}

SLOT_INFO::SLOT_INFO()
{
	memset(this, 0, sizeof SLOT_INFO);
}

SLOT_INFO::SLOT_INFO(int itemid, int stackCount, int * crystals, byte crystalCount, IItem * item, byte enchantLevel, int binderEI, int crafterEI)
{
	_itemId = itemid;
	_stackCount = stackCount;
	_hasCrystals = crystalCount;
	memset(crystals, 0, sizeof(int) * 4);
	for (byte i = 0; i < crystalCount; i++)
		_crystals[i] = crystals[i];

	_item = item;
	_isBinded = binderEI == 0 ? 0 : 1;
	_binderEntityId = binderEI;
	_isCrafted = crafterEI == 0 ? 0 : 1;
	_crafterEntityId = crafterEI;
	_enchantLevel = enchantLevel;
}

void SLOT_INFO::Clear()
{
	_passivities.clear();
	memset(this, 0, sizeof SLOT_INFO);
}

const bool SLOT_INFO::CanStack()
{
	return _stackCount + 1 <= _item->_maxStack;
}

const bool SLOT_INFO::Stack()
{
	if (!CanStack())
		return false;
	_stackCount++;

	return true;
}

const bool SLOT_INFO::operator==(SLOT_INFO* inf)
{
	if (_binderEntityId == inf->_binderEntityId &&
		_crafterEntityId == inf->_crafterEntityId&&
		_hasCrystals == inf->_hasCrystals &&
		_itemId == inf->_itemId &&
		_enchantLevel == inf->_enchantLevel&&
		_isMasterworked == inf->_isMasterworked&&
		_isAwakened == inf->_isAwakened&&
		_isBinded == inf->_isBinded &&
		_binderEntityId == inf->_binderEntityId&&
		_isEnigmatic == inf->_isEnigmatic)
		return true;

	return false;
}

const bool SLOT_INFO::operator=(SLOT_INFO * inf)
{
	if (!inf || (memcpy_s(this, sizeof SLOT_INFO, inf, sizeof SLOT_INFO) != 0))
		return false;
	return true;
}
