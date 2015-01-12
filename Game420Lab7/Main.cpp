#include "SDL.h"
#include "GameWorld.h"
#include "InputManager.h"
#include "StateManager.h"

#define SCREEN_WIDTH	1200
#define SCREEN_HEIGHT	750
#define SCREEN_DEPTH	32

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_WM_SetCaption("SDL_OpenGL + Box2D", NULL );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // for OpenGL double buffering
	SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH, SDL_OPENGL);

	if (screen != NULL)
	{
		GameWorld gameWorld;
		gameWorld.InitOpenGL(SCREEN_WIDTH, SCREEN_HEIGHT);
		gameWorld.CreateBox2DWorld();

		bool quit = false;
		SDL_Event event;
		StateManager::GetInstance()->SetCurrentState(StateManager::State::Game);
		//StateManager::GetInstance()->SetCurrentState(StateManager::State::Exit);

		while (quit == false) 
		{
			if (StateManager::GetInstance()->GetCurrentState()==StateManager::State::Game)
				{
					gameWorld.Update(0.0016f);
					gameWorld.Render();

				}
			// Check User Input & Events
			if (SDL_PollEvent(&event)) 
			{
				//everytime theres an event sdl will let the manager know
				InputManager::GetInstance()->Update(event);
				switch (event.type)
				{		
				case SDL_QUIT:
					quit = true;
					break;
				}			
			}
			//gameWorld.Update(0.0016f);
			//gameWorld.Render();
			//SDL_Delay(33);
						
			SDL_GL_SwapBuffers(); //instead of SDL_Flip(screen)			
			
		}
			
		SDL_FreeSurface(screen);
	}

	SDL_Quit();
	return 0;
}