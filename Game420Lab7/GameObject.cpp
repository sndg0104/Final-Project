#include "GameObject.h"
#include "SDL.h"
#include <assert.h>

GameObject::GameObject(b2World* world)
	:world(world)
{	
}


GameObject::~GameObject(void)
{
}


void GameObject::AddForce(b2Vec2 force)
{
	body->ApplyLinearImpulse(force, body->GetPosition(), true);
	//body->ApplyForce(force, body->GetPosition(), true);
}

void GameObject::LoadTexture(const char* fileName, bool bMask /* = false*/)
{
	assert(fileName);

	SDL_Surface* surface = SDL_LoadBMP(fileName);
	//assert(surface);
	//SDL_Surface* surface = SDL_DisplayFormat(surface_image);
    
    // Check that the image's width is a power of 2
    assert( (surface->w & (surface->w - 1)) == 0 );
    // Also check if the height is a power of 2
    assert( (surface->h & (surface->h - 1)) == 0 ); 
        
	if (bMask)
	{
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &mask );
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, mask );
	}
	else
	{
		// Have OpenGL generate a texture object handle for us
		glGenTextures( 1, &texture );
		// Bind the texture object
		glBindTexture( GL_TEXTURE_2D, texture );
	}
        
    // Set the texture's stretching properties
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        
    // Edit the texture object's image data using the information SDL_Surface gives us
    glTexImage2D( GL_TEXTURE_2D, 0, 3, surface->w, surface->h, 0, 
                    GL_BGR, GL_UNSIGNED_BYTE, surface->pixels );
    
    SDL_FreeSurface( surface );  
	//SDL_FreeSurface( surface_image );
}
