#include "World.h"
#include "JobSystem.h"
#include "ScopeLock.h"

void World::AddNewGameObject(StrongPtr<GameObject> i_GameObject)
{
	if (i_GameObject) {
		Engine::JobSystem::ScopeLock Lock(m_NewGameObjectMutex);
		m_NewGameObjects.push_back(i_GameObject);
	}
}

void World::CheckNewGameObjects()
{
	Engine::JobSystem::ScopeLock Lock(m_NewGameObjectMutex);
	for (auto it = m_NewGameObjects.begin(); it != m_NewGameObjects.end(); ++it)
	{
		m_GameObjects.push_back(*it);
	}
	m_NewGameObjects.clear();
}
