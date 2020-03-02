#pragma once

class GameObject;
class BaseComponent
{
public:
	BaseComponent() {};
	virtual ~BaseComponent() {};
	virtual void Release() {};
	virtual void Update(float DeltaTime) {};

public:
	// TODO delete gameObject
	GameObject* gameObject;
};
