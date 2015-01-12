#include "InputManager.h"
using namespace std;

//first time this header file is called it will initialize InputManager to a nullptr
InputManager* InputManager::Input=nullptr;

void InputManager::AddObserver(InputObserver* _AddObserver)
{
	ObserverList.push_back(_AddObserver);
}

void InputManager::RemoveObserver(InputObserver* _RemoveObserver)
{
	/*Every collection in c++ standard library has access to a class called iterator
	This provides a way to access elements in different containers easily.
	Here I create an iterator from the beginning of the ObserverList and loop through until
	I hit the iterator representing the end of the list.
	*/
	std::vector<InputObserver*>::iterator beginning = ObserverList.begin();

	for (beginning; beginning !=  ObserverList.end(); beginning++)
	{
		//If the current iterator is equal to the observer we want to remove, erase it
		//The * before beginning dereferences the iterator to give me access to the value it points to
		if(*beginning == _RemoveObserver)
			ObserverList.erase(beginning);
	}
}

void InputManager::Update(SDL_Event e)
{
	KeyboardEventArgs KeyArgs;
	MouseMovementEventArgs MovementArgs;
	MouseButtonEventArgs ButtonArgs;
	switch (e.type)
	{		
		case SDL_MOUSEMOTION:
			 MovementArgs = MouseMovementEventArgs(b2Vec2(e.motion.x, e.motion.y), b2Vec2(e.motion.xrel, e.motion.yrel));
			for (int i = 0; i < ObserverList.size(); i++)
			{
				//everytime theres a MouseEvent loop through and notify all the observers
				ObserverList[i]->OnMouseMove(MovementArgs);
			}
		break;
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			//
			 ButtonArgs = MouseButtonEventArgs(e.button.button, e.button.state, b2Vec2(e.button.x, e.button.y));
			for (int i = 0; i < ObserverList.size(); i++)
			{
				//everytime theres a ButtonEvent loop through and notify all the observers
				ObserverList[i]->OnMouseButton(ButtonArgs);
			}
		break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:
		{
			KeyArgs = KeyboardEventArgs(e.key.keysym, e.key.state);
			for (int i = 0; i < ObserverList.size(); i++)
			{
				//everytime theres a KeyboardEvent loop through and notify all the observers
				ObserverList[i]->OnKeyEvent(KeyArgs);
			}
		}
		break;
	}		
}

InputManager::InputManager(void)
{
}


InputManager::~InputManager(void)
{
}
