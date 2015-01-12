#include "GameWorld.h"
#include "GameObject.h"
#include "SDL_opengl.h"
#include <glut.h>
#include "Ground.h"
#include "Ball.h"
#include "WoodenBox.h"
#include "StoneBlock.h"
#include "Joint.h"
#include "LongBox.h"
#include "enemy.h"
#include "EndScreen.h"


GameWorld::GameWorld(void)
{
}


GameWorld::~GameWorld(void)
{
	while(objects.size())
	{
		delete objects.back();
		objects.pop_back();
	}
}

void GameWorld::CreateBox2DWorld()
{
	gameWon = false;
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
#if 1
	// Version 2.1.2
	world = new b2World(gravity);
#else
	// Version 2.2.1
	world = new b2World(gravity);
#endif
	//This is the background
	background = new Background(world);

	endscreen = new EndScreen(world);
#if 0
	// Define the ground body.
	b2BodyDef groundBodyDef;	
	//groundBodyDef.position.Set(0.0f, -10.0f);
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	//b2PolygonShape groundBox;
	b2EdgeShape groundBox;
	// The extents are the half-widths of the box.
	//groundBox.SetAsBox(50.0f, 10.0f);
	groundBox.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));
	
	//groundBody->
	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);
#endif
	objects.push_back(new Ground(world));

#if 0
	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 200.0f);
	//bodyDef.angularVelocity = 0.1f;

	b2Vec2 v(0, 1.0f);
	//bodyDef.linearVelocity = v;
	body = world->CreateBody(&bodyDef);
	body2 = world->CreateBody(&bodyDef);
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(2.0f, 2.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;
	// Override the default friction.
	//fixtureDef.friction = 0.3f;
	// Add the shape to the body.
	//fixtureDef.restitution = 0.5f;	
	
	body->CreateFixture(&fixtureDef);
	body2->CreateFixture(&fixtureDef);
#endif
	
	//Draws multiple wooden boxes
	for (int i = 0; i < 3; i++)
	{
		objects.push_back(new WoodenBox(world, 14.0f, 5.0f));
		objects.push_back(new WoodenBox(world, 25.0f, 5.0f));
	}

	objects.push_back(new LongBox(world, 19.5f, 15.0f));

	//gold box
	Enemy = new enemy(world, 19.5f, 20.0f);
	objects.push_back(Enemy);

	//Draw multiple barriers(stone blocks)
	objects.push_back(new StoneBlock(world, -4.0f, 6.0f));
	objects.push_back(new StoneBlock(world, -4.0f, 2.0f));

	StoneBlock* anchorblock = new StoneBlock(world, 4.0f, 35.0f);
	StoneBlock* anchorblock2 = new StoneBlock(world, 12.0f, 35.0f);

	objects.push_back(new StoneBlock(world, 0.0f, 35.0f));
	objects.push_back(anchorblock);//
	objects.push_back(new StoneBlock(world, 8.0f, 35.0f));
	objects.push_back(anchorblock2);//
	objects.push_back(new StoneBlock(world, 16.0f, 35.0f));

	objects.push_back(new StoneBlock(world, -10.0f, 47.0f));
	objects.push_back(new StoneBlock(world, -14.0f, 47.0f));
	objects.push_back(new StoneBlock(world, -18.0f, 47.0f));
	objects.push_back(new StoneBlock(world, -22.0f, 47.0f));
	objects.push_back(new StoneBlock(world, -26.0f, 47.0f));

	//Draws the ball
	//adding the ball to the objects vector
	ball = new Ball(world, -30.0f, 10.0f);
	//adding the objects back into the list
	objects.push_back(ball);

	joint = new Joint(world, anchorblock->body, b2Vec2(4.0f, 20.0f));
	joint2 = new Joint(world, anchorblock2->body, b2Vec2(12.0f, 20.0f));
	objects.push_back(joint);
	objects.push_back(joint2);
}

void GameWorld::InitOpenGL(int width, int height)
{
	// Set the OpenGL state after creating the context with SDL_SetVideoMode

	glClearColor( 0, 0, 0, 0 );
	
	glEnable( GL_TEXTURE_2D ); // Need this to display a texture

    glViewport( 0, 0, width, height );
	//glViewport( -60, 0, 500, 500 );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //glOrtho( -400, width-400, -30, height-30, -1, 1 );
	glOrtho( -40, 40, -5, 55, -1, 1 );
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void GameWorld::Update(float time)
{
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(time, velocityIterations, positionIterations);

	
	float currentPos = Enemy->body->GetPosition().y;
	if(currentPos <= 3)
	{
	gameWon = true;	
	}
}

void GameWorld::Render()
{
	// Clear the screen before drawing
	glClear( GL_COLOR_BUFFER_BIT );

	background->Render();

	if(gameWon)
	{
		glClear( GL_COLOR_BUFFER_BIT );
		endscreen->Render();
	}

	int count = objects.size();
	for(int i = 0; i < count; i++) objects[i]->Render();
}



void GameWorld::OnKeyEvent()
{
	//adds force to the objects along x and y
	//ball->AddForce(b2Vec2(200.0f, 100.0f));
}