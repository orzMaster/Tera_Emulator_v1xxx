#include "EntityService.h"
#include "Entity.h"
#include "DropEntity.h"
#include "ItemEntity.h"

unsigned int EntityService::GenerateId()
{
	std::lock_guard<std::mutex> _lock(_generateMutex);
	_lastId++;
	return _lastId;
}

unsigned int EntityService::GenerateDropId()
{
	std::lock_guard<std::mutex> lock(_generateDropMutex);
	_lastDropId++;
	return _lastDropId;
}

unsigned int EntityService::GenerateItemId()
{
	std::lock_guard<std::mutex> _lock(_generateItemMutex);
	_lastItemId++;
	return _lastItemId;
}

void EntityService::Initialize()
{

}

Entity * EntityService::GetEntity(unsigned int id)
{
	Entity*  out = nullptr;
	std::lock_guard<std::mutex> _lock(_getEntityMutex);
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i] && _entities[i]->_entityId == id)
			out = _entities[i];
	}
	return out;
}

DropEntity * EntityService::GetDropEntity(unsigned int id)
{
	DropEntity*  out = nullptr;
	std::lock_guard<std::mutex> _lock(_getDropEntityMutex);
	for (size_t i = 0; i < _dropEntities.size(); i++)
	{
		if (_dropEntities[i] && _dropEntities[i]->_entityId == id)
			out = _dropEntities[i];
	}
	return out;
}

ItemEntity * EntityService::GetItemEntity(unsigned int id)
{
	ItemEntity*  out = nullptr;
	std::lock_guard<std::mutex> _lock(_getItemEntityMutex);
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_itemEntities[i] && _itemEntities[i]->_entityId == id)
			out = _itemEntities[i];
	}
	return out;
}

void EntityService::Add(Entity * e)
{
	e->_entityId = GenerateId();
	std::lock_guard<std::mutex> _lock(_getEntityMutex);
	_entities.push_back(e);
	
}

void EntityService::Remove(Entity * e)
{
	std::lock_guard<std::mutex> _lock(_getEntityMutex);
	for (size_t i = 0; i < _entities.size(); i++)
	{
		if (_entities[i] == e)
		{
			_entities[i] = 0;
			_entities.erase(_entities.begin() + i);
			break;
		}
	}
	
}

void EntityService::Add(DropEntity * e)
{
	e->_entityId = GenerateDropId();
	std::lock_guard<std::mutex> lock(_getDropEntityMutex);
	_dropEntities.push_back(e);
}

void EntityService::Remove(DropEntity * e)
{
	std::lock_guard<std::mutex> _lock(_getDropEntityMutex);
	for (size_t i = 0; i < _dropEntities.size(); i++)
	{
		if (_dropEntities[i] == e)
		{
			_dropEntities[i] = nullptr;
			_dropEntities.erase(_dropEntities.begin() + i);
			break;
		}
	}
}

void EntityService::Add(ItemEntity * e)
{
	e->_entityId = GenerateItemId();
	std::lock_guard<std::mutex> lock(_getItemEntityMutex);
	_itemEntities.push_back(e);
}

void EntityService::Remove(ItemEntity * e)
{
	std::lock_guard<std::mutex> _lock(_getItemEntityMutex);
	for (size_t i = 0; i < _itemEntities.size(); i++)
	{
		if (_itemEntities[i] == e)
		{
			_itemEntities[i] = nullptr;
			_itemEntities.erase(_itemEntities.begin() + i);
			break;
		}
	}
}

unsigned int EntityService::_lastId = 0;
unsigned int EntityService::_lastItemId = 0;
unsigned int EntityService::_lastDropId = 0;
std::mutex   EntityService::_generateMutex;
std::mutex   EntityService::_getEntityMutex;
std::mutex   EntityService::_generateDropMutex;
std::mutex   EntityService::_getDropEntityMutex;
std::mutex	 EntityService::_generateItemMutex;
std::mutex	 EntityService::_getItemEntityMutex;
std::vector<Entity*> EntityService::_entities;
std::vector<DropEntity*> EntityService::_dropEntities;
std::vector<ItemEntity*>  EntityService::_itemEntities;