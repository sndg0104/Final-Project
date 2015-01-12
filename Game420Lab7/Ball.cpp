#include "Ball.h"
#include "InputManager.h"

static const float BALL_RADIUS = 1.5f;
bool hasfired;
int counter;
float currentVel;
bool isgrounded;
float speed = 45.0f;

Ball::Ball(b2World* world, float x, float y)
	:GameObject(world)
{

	trajectory = b2Vec2 (45.0f, 45.0f);
	trajectory.Normalize();
	angle = 8.0f;
	counter = 0;
	hasfired = false;
	isgrounded = true;
	currentVel = 0;
	CreateBox2dObject(x, y);
	LoadTexture("images\\alien.bmp");
	LoadTexture("images\\soccerball_mask.bmp", true);
	InputManager::GetInstance()->AddObserver(this);
}

Ball::~Ball(void)
{
}

bool Ball::ballcollide(b2CircleShape* circle, b2Vec2 point)
{
	//point is the mouse
	b2Vec2 DistanceBetween = (circle->m_p+body->GetPosition()) - point;
	float HoldDistance = DistanceBetween.Length();
printf("%f, %f \n", point.x, point.y);
	//if the point is less then the radius of the circle, then the mouse is inside the circle
	//true if the point is inside circle, false if it isn't
	return HoldDistance <= circle->m_radius;
}

b2Vec2 Ball::RotateVec(b2Vec2 e, float angle)
{
	//convert degrees to radians
	angle = angle * (3.14159265/180);

	b2Vec2 temp;
	temp.x = e.x * cosf(angle) - e.y * sinf(angle);
	temp.y = e.x * sinf(angle) + e.y * cosf(angle);
	return temp;
}

void Ball::OnKeyEvent(KeyboardEventArgs e)
{
	//if the keyboard is pushed down check which key
	if(e.KeyboardState == SDL_PRESSED)
	{		
		//if the key pressed down is the up arrow, aim catapult up
		if (e.KeyboardSym.sym == SDLK_UP)
		{
			printf("hey im pressing up");
			trajectory = RotateVec(trajectory, angle);
		}
		//if the key pressed down is the down arrow, aim catapult down
		if (e.KeyboardSym.sym == SDLK_DOWN)
		{
			printf("hey im pressing down");
			trajectory = RotateVec(trajectory, -angle);
		}

		if (!hasfired)
		{				
			if(e.KeyboardSym.sym == SDLK_SPACE)
			{
				if(counter <= 5)
				{
				body->SetLinearVelocity(speed * trajectory);
						
						
				//hasfired = true;
				isgrounded = false;
				}
				currentVel = body->GetLinearVelocity().Length();
				counter++;
			}
		}
	}		
}

void Ball::OnMouseButton(MouseButtonEventArgs e)
{
	/*if (e.ButtonIndex == SDL_BUTTON_LEFT)
	{	
		if (e.ButtonState == SDL_PRESSED)
		{
			
			b2CircleShape* shape;
			shape = (b2CircleShape*)body->GetFixtureList()->GetShape();
			
			b2Vec2 mouse = b2Vec2(e.MousePosition.x / 1200, e.MousePosition.y / 800);
			mouse.x -= 0.5f;
			mouse.y = -mouse.y;
			mouse.y += 0.5f;

			if (ballcollide(shape, mouse) == true)
			{
				ballhold = true;
			}
			
		}
	}*/
}

void Ball::OnMouseMove(MouseMovementEventArgs e)
{
	//if (ballhold == true)
	//{
	//	//setting the balls position to the mouse's position
	//	body->SetTransform(e.MouseMovement, 0);
	//	printf("Left Button Down!");
	//}
	
}

void Ball::Update(float time)
{
}

void Ball::CreateBox2dObject(float x, float y)
{
	// Circle
	b2CircleShape shape;
	shape.m_radius = BALL_RADIUS;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 1.0f;
	fd.restitution = 0.5f;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(x, y);
	body = world->CreateBody(&bd);
	body->CreateFixture(&fd);

	if(currentVel > 0.0f)
	{						
		hasfired = true;
		isgrounded = false;
	}
						
	if (currentVel <= 0.0f)
	{			
		isgrounded = true;
		hasfired = false;
	}
}

void Ball::Render()
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
		glVertex2f(-BALL_RADIUS, BALL_RADIUS);
		glTexCoord2i( 0, 0 );
		glVertex2f(-BALL_RADIUS, -BALL_RADIUS);
		glTexCoord2i( 1, 0 );
		glVertex2f(BALL_RADIUS, -BALL_RADIUS);
		glTexCoord2i( 1, 1 );
		glVertex2f(BALL_RADIUS, BALL_RADIUS);
	glEnd();	
#endif
	glBlendFunc(GL_ONE, GL_ONE);    
	glBindTexture( GL_TEXTURE_2D, texture );
#if 1
	glBegin(GL_QUADS);
		glTexCoord2i( 0, 1 );
		glVertex2f(-BALL_RADIUS, BALL_RADIUS);
		glTexCoord2i( 0, 0 );
		glVertex2f(-BALL_RADIUS, -BALL_RADIUS);
		glTexCoord2i( 1, 0 );
		glVertex2f(BALL_RADIUS, -BALL_RADIUS);
		glTexCoord2i( 1, 1 );
		glVertex2f(BALL_RADIUS, BALL_RADIUS);
	glEnd();
#endif

	glDisable(GL_BLEND);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glLineWidth(1.5);
	glBegin(GL_LINES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(trajectory.x * 5, trajectory.y * 5);
	glEnd();
	glPopMatrix();
}