#include "ItemEntity.h"
#include "EntityService.h"


ItemEntity::ItemEntity()
{
	
}


ItemEntity::~ItemEntity()
{
	EntityService::Remove(this);
}
