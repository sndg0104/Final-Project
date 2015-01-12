#include "gameobject.h"
#include "InputObserver.h"

class Joint :
	public GameObject
{
private:
	b2Body* anchor;
public:
	Joint(b2World* world, b2Body* body, b2Vec2 vec);
	~Joint();

	void CreateBox2dObject(float x, float y){}
	void CreateBox2dObject(b2Body* body, b2Vec2 vec);
	void Render();
};
