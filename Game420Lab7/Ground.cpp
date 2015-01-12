#include "Ground.h"


Ground::Ground(b2World* world)
	:GameObject(world)
{
	CreateBox2dObject(0, 0);
}


Ground::~Ground(void)
{
}

void Ground::CreateBox2dObject(float x, float y)
{
	// Define the ground body.
	b2BodyDef groundBodyDef;	
	//groundBodyDef.position.Set(0.0f, -10.0f);
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	body = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
#if 1
	// Version 2.1.2
	//b2PolygonShape groundBox; 

	//half width, half height, the position of the line, and the angle

	//*!The ground box order is bottom, right, top, left!*//
	b2EdgeShape groundBox;
	b2EdgeShape groundBox1;
	b2EdgeShape groundBox2;
	b2EdgeShape groundBox3;
	//This method is for drawing the line
	groundBox.Set(b2Vec2(-39.0f, 0.0f), b2Vec2(39.0f, 0.0f));
	groundBox1.Set(b2Vec2(39.0f, 0.0f), b2Vec2(39.0f, 54.0f));
	groundBox2.Set(b2Vec2(39.0f, 54.0f), b2Vec2(-39.0f, 54.0f));
	groundBox3.Set(b2Vec2(-39.0f, 0.0f), b2Vec2(-39.0f, 54.0f));
	//groundBox.SetAsBox(40, 1, b2Vec2(0.0, 0.0),0.0);
		//SetAsEdge(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 10.0f));
#else
	//// Version 2.2.1
	//b2EdgeShape groundBox;
	//b2EdgeShape groundBox1;
	//b2EdgeShape groundBox2;
	//b2EdgeShape groundBox3;
	//// The extents are the half-widths of the box.
	//
	//groundBox.Set(b2Vec2(-50.0f, 0.0f), b2Vec2(80.0f, 0.0f));
	//groundBox1.Set(b2Vec2(35.0f, 0.0f), b2Vec2(35.0f, 50.0f));
	//groundBox2.Set(b2Vec2(39.0f, 54.0f), b2Vec2(-39.0f, 54.0f));
	//groundBox3.Set(b2Vec2(-35.0f, 0.0f), b2Vec2(-35.0f, 50.0f));

#endif	
	// Add the ground fixture to the ground body.
	body->CreateFixture(&groundBox, 0.0f);
	body->CreateFixture(&groundBox1, 0.0f);
	body->CreateFixture(&groundBox2, 0.0f);
	body->CreateFixture(&groundBox3, 0.0f);
}

void Ground::Render()
{
	//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
	//groundbox
	glDisable(GL_TEXTURE_2D);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);		
		glVertex2f(-40.0f, 0.0f);
		//This vertor is for the line
		glVertex2f(40.0f, 0.0f);
	glEnd();
	//groundbox1
	glBegin(GL_LINES);		
		glVertex2f(40.0f, 0.0f);
		//This vertor is for the line
		glVertex2f(40.0f, 55.0f);
	glEnd();
	//groundbox2
	glBegin(GL_LINES);		
		glVertex2f(40.0f, 55.0f);
		//This vertor is for the line
		glVertex2f(-40.0f, 55.0f);
	glEnd();
	//groundbox3
	glBegin(GL_LINES);		
		glVertex2f(-40.0f, 0.0f);
		//This vertor is for the line
		glVertex2f(-40.0f, 55.0f);
	glEnd();
}