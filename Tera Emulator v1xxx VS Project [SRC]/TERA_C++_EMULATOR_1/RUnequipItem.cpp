#include "RUnequipItem.h"
#include "Inventory.h"
#include "MessagingSystem.h"

RUnequipItem::RUnequipItem() :SendPacket(C_UNEQUIP_ITEM)
{
}

void RUnequipItem::Process(OpCode opCode, Stream * data, Client * caller) const
{

	int playerId = data->ReadInt32();
	int playerSubId = data->ReadInt32();

	int prfileslotId = data->ReadInt32();
	int inventorySlotId = data->ReadInt32();
	int item = data->ReadInt32();

	Player * p = caller->GetSelectedPlayer();
	if (!p)
		return;
	Inventory *iv = p->_inventory;
	InventorySlot* invSlot = nullptr, *profSlot = nullptr;
	if (!(invSlot = iv->IsFull()))
	{
		MessagingSystem::SendSystemMessage(caller, "@39");
		return;
	}
	if (!(profSlot = (*iv)[prfileslotId]))
		return;


	iv->Lock();
	(*invSlot) ^ profSlot;
	iv->Unlock();

	iv->SendInventory(caller, 0);
}
