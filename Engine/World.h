#pragma once
#include <vector>
#include "SmartPtr.h"
#include "GameObject.hpp"
#include "Mutex.h"

using namespace std;

class World
{
public:
	inline vector<StrongPtr<GameObject>> GetGameObjects() const { return m_GameObjects; }
	void AddNewGameObject(StrongPtr<GameObject> i_GameObject);
	void CheckNewGameObjects();
private: 
	vector<StrongPtr<GameObject>> m_GameObjects;
	vector<StrongPtr<GameObject>> m_NewGameObjects;
	Engine::JobSystem::Mutex m_NewGameObjectMutex;
};

