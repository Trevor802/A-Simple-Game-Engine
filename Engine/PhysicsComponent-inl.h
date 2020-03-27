#pragma once
#include "PhysicsComponent.h"

inline Vector2 PhysicsComponent::GetVelocity() const { return this->Velocity; }
inline void PhysicsComponent::SetVelocity(const Vector2 InVelocity) { this->Velocity = InVelocity; }
inline void PhysicsComponent::AddVelocity(const Vector2 InVelocityChange) { this->Velocity += InVelocityChange; }
inline void PhysicsComponent::SetForce(const Vector2 InForce) { this->Force = InForce; }
inline void PhysicsComponent::AddForce(const Vector2 InForce) { 
	this->ExternalForce = InForce;
}