#include "StateManager.h"


StateObserver::StateObserver()
{
}

StateObserver::~StateObserver()
{
}

StateManager* StateManager::Singleton=nullptr;

void StateObserver::OnStateChange(StateManager::State NewState)
{
}

StateManager::State StateManager::GetCurrentState()
{
	return CurrentState;
}

void StateManager::SetCurrentState(State state)
{
	CurrentState = state;

	for (int i = 0; i < ObserverList.size(); i++)
	{
		ObserverList[i]->OnStateChange(state);
	}
}

void StateManager::AddObserver(StateObserver* _AddObserver)
{
	ObserverList.push_back(_AddObserver);
}

void StateManager::RemoveObserver(StateObserver* _RemoveObserver)
{
	/*Every collection in c++ standard library has access to a class called iterator
	This provides a way to access elements in different containers easily.
	Here I create an iterator from the beginning of the ObserverList and loop through until
	I hit the iterator representing the end of the list.
	*/
	std::vector<StateObserver*>::iterator beginning = ObserverList.begin();

	for (beginning; beginning !=  ObserverList.end(); beginning++)
	{
		//If the current iterator is equal to the observer we want to remove, erase it
		//The * before beginning dereferences the iterator to give me access to the value it points to
		if(*beginning == _RemoveObserver)
			ObserverList.erase(beginning);
	}
}

StateManager::StateManager()
{
}


StateManager::~StateManager()
{
}
