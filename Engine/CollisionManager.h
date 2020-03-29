#pragma once
#include "GameObject.hpp"
#include "SmartPtr.h"
#include <vector>
#include "World.h"
#include "GameObject.hpp"
#include "Collider.h"
class CollisionManager
{
public:
	void SetColliders(World* i_world) {
		m_Colliders.clear();
		for (auto it = i_world->GetGameObjects().begin(); it != i_world->GetGameObjects().end(); it++) {
			if ((*it)->HasComponent<Collider>())
				m_Colliders.push_back((*it)->GetComponent<Collider>());
		}
	}
	void ProcessCollision(const Collider& i_lhs, const Collider& i_rhs) const {

	}
	void ProcessCollisions() const {
		for (int i = 0; i < m_Colliders.size() - 1; i++) {
			for (int j = i + 1; j < m_Colliders.size(); j++) {
				ProcessCollision(m_Colliders[i].Acquire(), m_Colliders[j].Acquire());
			}
		}
	}
private:
	vector<WeakPtr<Collider>> m_Colliders;
};

