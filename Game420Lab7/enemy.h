#pragma once
#include "GameObject.h"
class enemy:
	public GameObject
{
public:
	enemy(b2World* world, float x, float y);
	~enemy(void);

	void CreateBox2dObject(float x, float y);
	void Render();
};

