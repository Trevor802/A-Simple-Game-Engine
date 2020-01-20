#pragma once
#include "BaseComponent.h"
#include "Vector2D.hpp"
class PhysicsComponent : public BaseComponent
{
public:
	PhysicsComponent() : BaseComponent() { };
	void Update(float DeltaTime) override;

	inline Vector2D GetVelocity() const;
	inline void SetVelocity(const Vector2D InVelocity);
	inline void AddVelocity(const Vector2D InVelocityChange);
	inline void SetForce(const Vector2D InForce);
	inline void AddForce(const Vector2D InForce);

public:
	bool bUseGravity = false;
	float DragCoefficient = .1f;
	float Inertia = .1f;
	float Mass = 10;

private:
	const float Gravity = -9.8f;
	Vector2D Velocity;
	Vector2D Force;
	Vector2D ExternalForce;
};

#include "PhysicsComponent-inl.h"