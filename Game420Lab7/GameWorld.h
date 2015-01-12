#pragma once
#include "Box2D/Box2D.h"
#include "SDL_opengl.h"
#include <vector>
#include "GameObject.h"
#include "Background.h"
#include "EndScreen.h"

class GameWorld
{
	b2World* world;
	std::vector<GameObject*> objects;

	Background* background;
	EndScreen* endscreen;

	GameObject *ball;
	GameObject *Enemy;
	GameObject *joint;
	GameObject *joint2;

public:
	GameWorld(void);
	~GameWorld(void);
	
	bool gameWon;

	void LoadTexture(const char* fileName, bool bMask = false);	

	void CreateBox2DWorld();
	void InitOpenGL(int width, int height);
	void Update(float time);
	void Render();
	void OnKeyEvent();
};

