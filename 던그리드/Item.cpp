#include "stdafx.h"
#include "Item.h"



Item::Item(){} Item::~Item(){}

HRESULT Item::init()
{

	return S_OK;
}


void Item::release()
{

}


void Item::update()
{

	
}


void Item::render() // 아이템을 렌더
{


}

void Item::ItemDirection()
{


	switch (_condition)
	{
		case DROPITEM:
		break;
		case INVENITEM:
		break;
		case WEARITEM:
		break;
	}

	if (_isInvenItem)
	{

	}
	else
	{

	}

	if (_isWearItem)
	{

	}
	else
	{

	}

}

void Item::setDropItem()
{
	if (_isDropItem)
	{

	}

}


void Item::setInvenItem()
{
	if (_isInvenItem)
	{

	}
	else
	{

	}
}

void Item::setWearItem()
{

}

