#pragma once

#include <mutex>
#include <vector>

class Entity; class DropEntity; class ItemEntity;
class EntityService
{
public:
	static void Add(Entity* e);
	static void Remove(Entity * e);

	static void Add(DropEntity* e);
	static void Remove(DropEntity * e);

	static void Add(ItemEntity* e);
	static void Remove(ItemEntity * e);

public:
	static unsigned int GenerateId();
	static unsigned int GenerateDropId();
	static unsigned int GenerateItemId();
	static void Initialize();
	static Entity * GetEntity(unsigned int id);
	static DropEntity* GetDropEntity(unsigned int id);
	static ItemEntity * GetItemEntity(unsigned int id);
private:
	static std::vector<Entity*> _entities;
	static std::vector<DropEntity*> _dropEntities;
	static std::vector<ItemEntity*> _itemEntities;
	static unsigned int _lastId;
	static unsigned int _lastDropId;
	static unsigned int _lastItemId;

	static std::mutex _generateMutex;
	static std::mutex _getEntityMutex;

	static std::mutex _generateDropMutex;
	static std::mutex _getDropEntityMutex;

	static std::mutex _generateItemMutex;
	static std::mutex _getItemEntityMutex;
};

