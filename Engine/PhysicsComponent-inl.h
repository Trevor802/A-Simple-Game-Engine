#pragma once
#include "PhysicsComponent.h"

inline Vector2D PhysicsComponent::GetVelocity() const { return this->Velocity; }
inline void PhysicsComponent::SetVelocity(const Vector2D InVelocity) { this->Velocity = InVelocity; }
inline void PhysicsComponent::AddVelocity(const Vector2D InVelocityChange) { this->Velocity += InVelocityChange; }
inline void PhysicsComponent::SetForce(const Vector2D InForce) { this->Force = InForce; }
inline void PhysicsComponent::AddForce(const Vector2D InForce) { 
	this->ExternalForce = InForce;
}