#include "stdafx.h"
#include "GodNpc.h"


GodNpc::GodNpc(){} GodNpc::~GodNpc(){}

HRESULT GodNpc::init()
{

	return S_OK;
}

void GodNpc::update()
{

}

void GodNpc::release()
{
}

void GodNpc::render()
{
	_image->frameRender(DC, _npcX, _npcY, _image->getFrameWidth(),
		_image->getFrameHeight());
}


void GodNpc::npcCreate(NPCTYPE type, const char* npcName, POINT position)
{

}


void GodNpc::WeaponNpc()
{


}


void GodNpc::FoodNpc()
{


}
