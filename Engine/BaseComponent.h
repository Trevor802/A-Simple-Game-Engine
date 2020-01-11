#pragma once

class GameObject;
class BaseComponent
{
public:
	//BaseComponent() {};
	BaseComponent(GameObject* i_pGameObject) : gameObject(i_pGameObject) {};
	virtual ~BaseComponent() {};
	virtual void Update() {};

public:
	GameObject* gameObject;
};

