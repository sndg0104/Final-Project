#pragma once
#include "GameObject.h"
class EndScreen :
	public GameObject
{
	
public:
	virtual void CreateBox2dObject(float x, float y);
	virtual void Render();
	EndScreen(b2World* world);
	~EndScreen(void);
};