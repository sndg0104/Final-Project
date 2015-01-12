#pragma once
#include "gameobject.h"
#include "InputObserver.h"

class Ball :
	public GameObject, public InputObserver
{
public:
	Ball(b2World* world, float x, float y);
	~Ball(void);

	void OnKeyEvent(KeyboardEventArgs);
	void OnMouseButton(MouseButtonEventArgs);
	void OnMouseMove(MouseMovementEventArgs);

	void CreateBox2dObject(float x, float y);
	void Render();
	void Update(float time);

	bool ballcollide(b2CircleShape* circle, b2Vec2 point);
	bool ballhold;

	b2Vec2 trajectory;
	float angle;
	b2Vec2 RotateVec(b2Vec2 e, float angle);
	

};

