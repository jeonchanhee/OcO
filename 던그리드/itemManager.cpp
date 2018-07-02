#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}


HRESULT itemManager::init()
{
	_item->init();

	return S_OK;
}


void itemManager::release()
{


}


void itemManager::update()
{

}


void itemManager::render()
{
	_item->render();

}
