#include "PhysicsComponent.h"
#include "GameObject.hpp"

void PhysicsComponent::Update(float DeltaTime)
{
	// Update velocity
	Velocity += Force / Mass * DeltaTime;
	// Update position
	gameObject->Move(Velocity * DeltaTime);
	// Update force
	// Clear force first
	Force = Vector2D();
	// gravity
	if (bUseGravity)
		Force += Vector2D(0, Gravity * Mass);
	// drag force
	Vector2D dragForce;
	if (Velocity.SqrMagnitude() < 10.0f)
		dragForce = Vector2D();
	else
		dragForce = Velocity.Normalize() * DragCoefficient * Velocity.SqrMagnitude();
	Force -= dragForce;
	// external force
	Force += ExternalForce;
}
