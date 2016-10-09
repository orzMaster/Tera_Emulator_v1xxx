#include "DropEntity.h"
#include "EntityService.h"


DropEntity::DropEntity()
{
	EntityService::Add(this);
}


DropEntity::~DropEntity()
{
	EntityService::Remove(this);
}

