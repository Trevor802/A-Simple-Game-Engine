#pragma once
#include "BaseComponent.h"
#include "CollisionManager.h"
struct CollisionParams;
class Collider :
	public BaseComponent
{
public:
	bool IsTrigger;
	virtual void OnCollisionEnter(const CollisionParams& params);
};

