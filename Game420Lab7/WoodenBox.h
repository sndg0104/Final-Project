#pragma once
#include "gameobject.h"
class WoodenBox :
	public GameObject
{
public:
	WoodenBox(b2World* world, float x, float y);
	~WoodenBox(void);

	void CreateBox2dObject(float x, float y);
	void Render();
};

