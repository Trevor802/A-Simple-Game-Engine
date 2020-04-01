#include "PhysicsComponent.h"
#include "GameObject.hpp"

void PhysicsComponent::Update(float DeltaTime)
{
	// Update velocity
	Velocity += Force / Mass * DeltaTime;
	// Update position
	gameObject->transform->Move(Velocity * DeltaTime);
	// Update force
	// Clear force first
	Force = Vector2();
	// gravity
	if (bUseGravity)
		Force += Vector2(0, Gravity * Mass);
	// drag force
	Vector2 dragForce;
	if (Velocity.SqrMagnitude() < 10.0f)
		dragForce = Vector2();
	else
		dragForce = Velocity.Normalize() * DragCoefficient * Velocity.SqrMagnitude();
	Force -= dragForce;
	// external force
	Force += ExternalForce;
}
