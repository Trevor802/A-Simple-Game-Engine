#pragma once
#include "GameObject.hpp"
#include "SmartPtr.h"
#include <vector>
class CollisionManager
{
public:
	vector<StrongPtr<GameObject>> GameObjects;
};

