#pragma once

class GameObject;
class BaseComponent
{
public:
	BaseComponent() {};
	virtual ~BaseComponent() {};
	virtual void Update(float DeltaTime) {};

public:
	GameObject* gameObject;
};
