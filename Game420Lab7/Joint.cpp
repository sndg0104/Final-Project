#include "Joint.h"
#include "GameObject.h"

static const float CIRCLE_RADIUS = 2.5f;

b2Body* ceiling = NULL;

Joint::Joint(b2World* world, b2Body* body, b2Vec2 vec)
	:GameObject(world)
{
	anchor = body;
	CreateBox2dObject(body, vec);
	LoadTexture("images\\wood_ball.bmp");
	LoadTexture("images\\soccerball_mask.bmp", true);
}


Joint::~Joint(void)
{
}


void Joint::CreateBox2dObject(b2Body* anchor, b2Vec2 vec)
{
	//b2BodyDef cd;
	//	ceiling = world->CreateBody(&cd);

	//	//the ceiling coordinates
	//	b2EdgeShape shape3;
	//	//so both the x numbers are the points that the line will be drawn between
	//	shape3.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
	//	//telling the body to draw a line
	//	ceiling->CreateFixture(&shape3, 0.0f);
	//	//moving the body up the y direction to 35
	//	ceiling->SetTransform(b2Vec2(0.0f, 15.0f),0);
	
		//circle
		b2CircleShape _circle;
		//the size of the circle
		_circle.m_radius = CIRCLE_RADIUS;

		b2FixtureDef pencircle;
		pencircle.shape = &_circle;
		pencircle.density = 0.2f;

		b2BodyDef pen;
		pen.type = b2_dynamicBody;
		pen.position.Set(vec.x, vec.y);

		body = world->CreateBody(&pen);
		body->CreateFixture(&pencircle);
		//b2Body* sscircle = world->CreateBody(&pen);
		//sscircle->CreateFixture(&pencircle);

		//creating a space between the pendulums

		b2Vec2 spacevar = anchor->GetWorldCenter();
		b2DistanceJointDef circlejoint;
		circlejoint.collideConnected = true;
		circlejoint.Initialize(body, anchor, body->GetWorldCenter(), spacevar);
		b2DistanceJoint* ceilingjoint = (b2DistanceJoint*)world->CreateJoint(&circlejoint);

}

void Joint::Render()
{
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotated(angle * 180 / 3.14159265, 0, 0, 1.0f);
	//glColor3f(1.0f, 1.0f, 1.0f);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture( GL_TEXTURE_2D, mask );
	//glColor4f(1.0f, 1.0f, 1.0f, 0.0f);
	
#if 1
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2f(-CIRCLE_RADIUS, CIRCLE_RADIUS);
		glTexCoord2i( 0, 0 );
		glVertex2f(-CIRCLE_RADIUS, -CIRCLE_RADIUS);
		glTexCoord2i( 1, 0 );
		glVertex2f(CIRCLE_RADIUS, -CIRCLE_RADIUS);
		glTexCoord2i( 1, 1 );
		glVertex2f(CIRCLE_RADIUS, CIRCLE_RADIUS);
	glEnd();	
#endif
	glBlendFunc(GL_ONE, GL_ONE);    
	glBindTexture( GL_TEXTURE_2D, texture );
#if 1
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2f(-CIRCLE_RADIUS, CIRCLE_RADIUS);
		glTexCoord2i( 0, 0 );
		glVertex2f(-CIRCLE_RADIUS, -CIRCLE_RADIUS);
		glTexCoord2i( 1, 0 );
		glVertex2f(CIRCLE_RADIUS, -CIRCLE_RADIUS);
		glTexCoord2i( 1, 1 );
		glVertex2f(CIRCLE_RADIUS, CIRCLE_RADIUS);
	glEnd();
#endif
	glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
	//glTranslatef(position.x, position.y, 0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glVertex2f(position.x, position.y);
	glVertex2f(anchor->GetPosition().x, anchor->GetPosition().y);
	glEnd();
	glPopMatrix();
}