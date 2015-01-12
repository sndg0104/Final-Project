#pragma once
#include "GameObject.h"

class LongBox :
	public GameObject
{
public:
	LongBox(b2World* world, float x, float y);
	~LongBox(void);

	void CreateBox2dObject(float x, float y);
	void Render();
};

