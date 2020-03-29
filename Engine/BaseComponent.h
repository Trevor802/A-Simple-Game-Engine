#pragma once
#include "SmartPtr.h"

class GameObject;
class BaseComponent
{
public:
	BaseComponent() {};
	virtual ~BaseComponent() {};
	virtual void Release() {};
	virtual void Update(float DeltaTime) {};

public:
	WeakPtr<GameObject> gameObject;
};
