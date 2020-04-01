#include "Collider.h"
#include "PhysicsComponent.h"
#include "Vector2.hpp"
#include "SmartPtr.h"

void Collider::OnCollisionEnter(const CollisionParams& params)
{
	WeakPtr<PhysicsComponent> p1 = gameObject->GetComponent<PhysicsComponent>();
	WeakPtr<PhysicsComponent> p2 = params.other->gameObject->GetComponent<PhysicsComponent>();
	Vector2 newV1 = (p1->GetVelocity() - 
		2.0f * p1->GetVelocity().DotProduct(params.normal.ToVector2()) * params.normal.ToVector2()).Normalize();
	Vector2 newV2 = p1->GetVelocity().Normalize();
	float v1 = p1->GetVelocity().Magnitude();
	float v2 = p2->GetVelocity().Magnitude();
	float m1 = p1->Mass;
	float m2 = p2->Mass;
	float s1 = (m1 - m2) / (m1 + m2) * v1 + 2 * m2 / (m1 + m2) * v2;
	float s2 = (m2 - m1) / (m1 + m2) * v2 + 2 * m1 / (m1 + m2) * v1;
	newV1 = newV1 * s1;
	newV2 = newV2 * s2;
	p1->SetVelocity(newV1);
	p2->SetVelocity(newV2);
}
