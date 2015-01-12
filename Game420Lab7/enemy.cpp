#include "enemy.h"


enemy::enemy(b2World* world, float x, float y)
	:GameObject(world)
{
	CreateBox2dObject(x, y);
	LoadTexture("images\\enemy.bmp");
}


enemy::~enemy(void)
{
}

void enemy::CreateBox2dObject(float x, float y)
{
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 50.0f);
	bodyDef.position.Set(x, y);
	bodyDef.angularVelocity = 0.0f;

	b2Vec2 v(0, 1.0f);
	//bodyDef.linearVelocity = v;
	body = world->CreateBody(&bodyDef);
	
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2.5f, 2.5f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 0.5f;
	// Override the default friction.
	//fixtureDef.friction = 0.3f;
	// Add the shape to the body.
	//fixtureDef.restitution = 0.5f;	
	
	body->CreateFixture(&fixtureDef);	
}

void enemy::Render()
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotated(angle * 180 / 3.14159265, 0, 0, 1.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ZERO);   
    glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, texture );
	//glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2f(-2.5f, 2.5f);

		glTexCoord2i( 0, 0 );
		glVertex2f(-2.5f, -2.5f);

		glTexCoord2i( 1, 0 );
		glVertex2f(2.5f, -2.5f);

		glTexCoord2i( 1, 1 );
		glVertex2f(2.5f, 2.5f);
	glEnd();
	glPopMatrix();
}