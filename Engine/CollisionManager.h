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
	void ProcessCollisions(World* i_world) const {
		
	}
private:
	vector<WeakPtr<Collider>> m_Colliders;
};

