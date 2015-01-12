#pragma once
#include <vector>
#include "InputObserver.h"
#include <SDL_events.h>
//template for singleton
class InputManager
{
private:
	InputManager(void);
	static InputManager* Input;
	std::vector<InputObserver*> ObserverList;
public:
	~InputManager(void);
	void AddObserver(InputObserver*);
	void RemoveObserver(InputObserver*);
	void Update(SDL_Event);

	//if called the first time it will create the instance
	inline static InputManager* GetInstance()
	{
		if (Input == nullptr)
		{
			//initialized singleton instance
			Input = new InputManager();
		}	
		return Input;
	}
	void DestroyInput()
	{
		if (Input != nullptr)
		{
			delete(Input);
			Input = nullptr;
		}
	}
};

