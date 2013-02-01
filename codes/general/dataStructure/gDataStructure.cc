#include "DataStructure.h"

myList::myList()
{
	length = 10;
}

myList::myList(const myList& oList)
{
	this->length = oList.length;
	//oList.length = 8;
}

myList myList::operator = (const myList& oList)
{
	this->length = oList.length;
	return *this;
}

bool myList::operator == (const myList& firList)
{
	return firList.length == this->length;
}
