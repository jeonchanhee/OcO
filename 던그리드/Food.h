#pragma once
#include "Item.h"
class Food : public Item
{
private:

	tagItem		_food;
	const char* _foodName;
	int			_value;
	
public:
	Food();
	~Food();

	HRESULT init(ITEMTYPE type, const char* FoodName, int value, POINT position);
	void release();
	void update();
	void CreateFood(ITEMTYPE type, const char* FoodName, int value);
	void setFood(const char* FoodName, int value);
	void render();
};

