#pragma once
#include "BaseComponent.h"
#include "Vector2.hpp"
class PhysicsComponent : public BaseComponent
{
public:
	PhysicsComponent() : BaseComponent() { };
	void Update(float DeltaTime) override;

	inline Vector2 GetVelocity() const;
	inline void SetVelocity(const Vector2 InVelocity);
	inline void AddVelocity(const Vector2 InVelocityChange);
	inline void SetForce(const Vector2 InForce);
	inline void AddForce(const Vector2 InForce);

public:
	bool bUseGravity = false;
	float DragCoefficient = .1f;
	float Inertia = .1f;
	float Mass = 10;

private:
	const float Gravity = -49.0f;
	Vector2 Velocity;
	Vector2 Force;
	Vector2 ExternalForce;
};

#include "PhysicsComponent-inl.h"