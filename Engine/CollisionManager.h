#pragma once
#include "GameObject.hpp"
#include "SmartPtr.h"
#include <vector>
#include "World.h"
#include "GameObject.hpp"
#include "Collider.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "PhysicsComponent.h"
#include "TimeManager.h"
#include "Numeric.h"
#include <limits>
#include "GameObject.hpp"
using namespace Engine;
class Collider;
struct CollisionParams {
	float time;
	Vector3 normal;
	WeakPtr<Collider> other;
};
class CollisionManager
{
public:
	void SetColliders(World* i_world);
	void ProcessCollisions() const;
	bool CheckCollision(WeakPtr<Collider> a, WeakPtr<Collider> b, CollisionParams& o_params) const;
private:
	vector<WeakPtr<Collider>> m_Colliders;
};

