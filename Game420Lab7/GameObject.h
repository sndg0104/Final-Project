#pragma once
#include "Box2D/Box2D.h"
#include "SDL_opengl.h"
#include <glut.h>

class GameObject
{
protected:
	
	b2World* world;
	GLuint texture;
	GLuint mask;

public:
	b2Body* body;
	GameObject(b2World* world);
	virtual ~GameObject(void);

	void AddForce(b2Vec2);
	void LoadTexture(const char* fileName, bool bMask = false);	
	virtual void CreateBox2dObject(float x, float y) = 0;
	virtual void Render() = 0;
};

