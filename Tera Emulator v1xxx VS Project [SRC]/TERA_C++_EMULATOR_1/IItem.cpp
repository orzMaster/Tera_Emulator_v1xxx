#include "IItem.h"



IItem::IItem() :ItemEntity()
{
	memset(this, 0, sizeof IItem);
}


IItem::~IItem()
{
	
}

int IItem::operator()(int)
{
	return _id;
}


