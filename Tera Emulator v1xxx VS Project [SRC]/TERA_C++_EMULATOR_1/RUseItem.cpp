#include "RUseItem.h"
#include "Inventory.h"

RUseItem::RUseItem() : SendPacket(C_USE_ITEM)
{

}

void RUseItem::Process(OpCode opCode, Stream * data, Client * caller) const
{
	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;
	data->ReadInt64();
	int item= data->ReadInt32();
	int id = data->ReadInt32();
	
	data->ReadInt64();
	data->ReadInt64();
	data->ReadInt64();
	data->ReadInt32();

	float x = data->ReadFloat();
	float y = data->ReadFloat();
	float z = data->ReadFloat();
	int w = data->ReadInt32();

	data->ReadInt64();
	data->ReadInt16();
	data->ReadByte();

	data->Clear();
	p->_inventory->UseItem(caller,(*p->_inventory)[(long)id]);
}