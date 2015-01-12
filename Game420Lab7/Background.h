#include "GameObject.h"
class Background :
	public GameObject
{
	
public:
	virtual void CreateBox2dObject(float x, float y);
	virtual void Render();
	Background(b2World* world);
	~Background(void);
};

