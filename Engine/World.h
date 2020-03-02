#pragma once
#include <vector>
#include "SmartPtr.h"
#include "GameObject.hpp"

using namespace std;

class World
{
private: 
	vector<StrongPtr<GameObject>> m_GameObjects;
};

