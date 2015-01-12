#pragma once
#include <vector>
class StateObserver;
class StateManager
{
public:
	enum State
	{
		Invalid=0, Menu=1, Game=2, Options=3, Exit=4
	};

private:
	StateManager(void);
	static StateManager* Singleton;
	State CurrentState;

	std::vector<StateObserver*> ObserverList;
public:
	~StateManager(void);
	void AddObserver(StateObserver*);
	void RemoveObserver(StateObserver*);

	State GetCurrentState();
	void SetCurrentState(State state);

		//if called the first time it will create the instance
	inline static StateManager* GetInstance()
	{
		if (Singleton == nullptr)
		{
			//initialized singleton instance
			Singleton = new StateManager();
		}	
		return Singleton;
	}
	void DestroyState()
	{
		if (Singleton!= nullptr)
		{
			delete(Singleton);
			Singleton = nullptr;
		}
	}
};

class StateObserver
{
public:
	StateObserver();
	virtual ~StateObserver();

	void OnStateChange(StateManager::State NewState);
};
