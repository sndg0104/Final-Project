#pragma once
#include "gameobject.h"
class StoneBlock :
	public GameObject
{
public:
	StoneBlock(b2World* world, float x, float y);
	~StoneBlock(void);

	void CreateBox2dObject(float x, float y);
	void Render();
};

