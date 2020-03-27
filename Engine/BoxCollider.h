#pragma once
#include "Collider.h"
#include "Vector2.hpp"
class BoxCollider : public Collider
{
public:
	Vector2 Center;
	Vector2 Size;
};

