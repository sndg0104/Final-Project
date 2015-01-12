#include "Background.h"


Background::Background(b2World* world)
:GameObject(world)
{
	LoadTexture("images\\background.bmp");
}

void Background::Render()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);    
	glBindTexture( GL_TEXTURE_2D, texture );

	glPushMatrix();

	glTranslatef(0.0f, 25.0f, 0.0f);
	glScalef(50.0f, -40.0f, 1.0f);

	glBegin(GL_QUADS);
		glTexCoord2i(0, 1 );
		glVertex2f(-1, 1);
		glTexCoord2i( 0, 0 );
		glVertex2f(-1, -1);
		glTexCoord2i( 1, 0 );
		glVertex2f(1, -1);
		glTexCoord2i( 1, 1 );
		glVertex2f(1, 1);
	glEnd();	

	glDisable(GL_BLEND);
	glPopMatrix();
}

void Background::CreateBox2dObject(float x, float y)
{
}

Background::~Background(void)
{
}
