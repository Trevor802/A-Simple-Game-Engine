#pragma once
#include "GameObject.hpp"
#include "SmartPtr.h"
#include <vector>
#include "World.h"
#include "GameObject.hpp"
#include "Collider.h"
#include "BoxCollider.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "PhysicsComponent.h"
#include "TimeManager.h"
#include "Numeric.h"
#include <limits>
#include "GameObject.hpp"
using namespace Engine;
class CollisionManager
{
public:
	void SetColliders(World* i_world) {
		m_Colliders.clear();
		vector<StrongPtr<GameObject>> temp = i_world->GetGameObjects();
		for (auto it = temp.begin(); it != temp.end(); it++) {
			if ((*it)->HasComponent<Collider>())
				m_Colliders.push_back((*it)->GetComponent<Collider>());
		}
	}
	void ProcessCollisions() const {
		for (int i = 0; i < m_Colliders.size() - 1; i++) {
			for (int j = i + 1; j < m_Colliders.size(); j++) {
				ProcessCollision(m_Colliders[i].Acquire(), m_Colliders[j].Acquire());
			}
		}
	}
private:
	void ProcessCollision(Collider& a, Collider& b) const {
		BoxCollider* l = dynamic_cast<BoxCollider*>(&a);
		BoxCollider* r = dynamic_cast<BoxCollider*>(&b);
		if (!l || !r) return;
		GameObject A = l->gameObject.Acquire();
		GameObject B = r->gameObject.Acquire();

		Matrix4x4 mRot = Matrix4x4::CreateZRotation(A.GetRotRad());
		Matrix4x4 mTrans = Matrix4x4::CreateTranslation(A.GetPosition());
		Matrix4x4 mAToWorld = mTrans * mRot;
		Matrix4x4 mWorldToA = mAToWorld.getInverse();
		mRot = Matrix4x4::CreateZRotation(B.GetRotRad());
		mTrans = Matrix4x4::CreateTranslation(B.GetPosition());
		Matrix4x4 mBToWorld = mTrans * mRot;
		Matrix4x4 mWorldToB = mBToWorld.getInverse();

		Matrix4x4 mAToB = mWorldToB * mAToWorld;
		Matrix4x4 mBToA = mAToB.getInverse();

		Vector3 velAToB = A.GetComponent<PhysicsComponent>()->GetVelocity() - B.GetComponent<PhysicsComponent>()->GetVelocity();

		float lastCloseTime = FLT_MIN;
		float firstOpenTime = FLT_MAX;

		float nextFrameTime = Time::GetLastFixedFrameTime() + Time::fixedDeltaTime;

		// Check A to B
		Vector4 velAInB = mWorldToB * Vector4(velAToB, 0.0f);
		Vector4 projAToB_x = mAToB * Vector4(l->Size.x, 0, 0, 0);
		Vector4 projAToB_y = mAToB * Vector4(0, l->Size.y, 0, 0);
		Vector4 ACenterInB = mAToB * Vector3(l->Center);

		// x axis
			float lengthProjAOntoB_x = fabs(projAToB_x.GetX()) + fabs(projAToB_y.GetX());
			float BExtentsX = r->Size.x + lengthProjAOntoB_x;
			float BLeftX = r->Center.x - BExtentsX;
			float BRightX = r->Center.x + BExtentsX;
			bool isSeparateX = false;
			if (Numeric::AreEqual(velAInB.GetX(), 0.0f)) {
				// vel x equals to 0
				isSeparateX = ACenterInB.GetX() < BLeftX || ACenterInB.GetX() > BRightX;
			}
			else {
				// vel x not equals to 0
				float tClose = (BLeftX - ACenterInB.GetX()) / velAInB.GetX();
				float tOpen = (BRightX - ACenterInB.GetX()) / velAInB.GetX();
				if (tClose > tOpen) {
					float temp = tClose;
					tClose = tOpen;
					tOpen = temp;
				}
				isSeparateX = tOpen < 0 || tClose > nextFrameTime;
				if (tClose > lastCloseTime) lastCloseTime = tClose;
				if (tOpen < firstOpenTime) firstOpenTime = tOpen;
			}
			if (isSeparateX)
				return;
		// y axis
			float lengthProjAOntoB_y = fabs(projAToB_x.GetY()) + fabs(projAToB_y.GetY());
			float BExtentsY = r->Size.y + lengthProjAOntoB_y;
			float BLeftY = r->Center.y - BExtentsY;
			float BRightY = r->Center.y + BExtentsY;
			bool isSeparateY = false;
			if (Numeric::AreEqual(velAInB.GetY(), 0.0f)) {
				// vel y equals to 0
				isSeparateY = ACenterInB.GetY() < BLeftY || ACenterInB.GetY() > BRightY;
			}
			else {
				// vel x not equals to 0
				float tClose = (BLeftY - ACenterInB.GetY()) / velAInB.GetY();
				float tOpen = (BRightY - ACenterInB.GetY()) / velAInB.GetY();
				if (tClose > tOpen) {
					float temp = tClose;
					tClose = tOpen;
					tOpen = temp;
				}
				isSeparateY = tOpen < 0 || tClose > nextFrameTime;
				if (tClose > lastCloseTime) lastCloseTime = tClose;
				if (tOpen < firstOpenTime) firstOpenTime = tOpen;
			}
			if (isSeparateY)
				return;

		// Check B to A
		Vector4 velBInA = mWorldToA * Vector4(-velAToB, 0.0f);
		Vector4 projBToA_x = mBToA * Vector4(r->Size.x, 0, 0, 0);
		Vector4 projBToA_y = mBToA * Vector4(0, r->Size.y, 0, 0);
		Vector4 BCenterInA = mBToA * Vector3(r->Center);
		// x axis
			float lengthProjBOntoA_x = fabs(projBToA_x.GetX()) + fabs(projBToA_y.GetX());
			float AExtentsX = l->Size.x + lengthProjBOntoA_x;
			float ALeftX = l->Center.x - AExtentsX;
			float ARightX = l->Center.x + AExtentsX;
			isSeparateX = false;
			if (Numeric::AreEqual(velBInA.GetX(), 0.0f)) {
				isSeparateX = BCenterInA.GetX() < ALeftX || BCenterInA.GetX() > ARightX;
			}
			else {
				// vel x not equals to 0
				float tClose = (ALeftX - BCenterInA.GetX()) / velBInA.GetX();
				float tOpen = (ARightX - BCenterInA.GetX()) / velBInA.GetX();
				if (tClose > tOpen) {
					float temp = tClose;
					tClose = tOpen;
					tOpen = temp;
				}
				isSeparateX = tOpen < 0 || tClose > nextFrameTime;
				if (tClose > lastCloseTime) lastCloseTime = tClose;
				if (tOpen < firstOpenTime) firstOpenTime = tOpen;
			}
			if (isSeparateX)
				return;
		// y axis
			float lengthProjBOntoA_y = fabs(projBToA_x.GetY()) + fabs(projBToA_y.GetY());
			float AExtentsY = l->Size.y + lengthProjBOntoA_y;
			float ALeftY = l->Center.y - AExtentsY;
			float ARightY = l->Center.y + AExtentsY;
			isSeparateY = false;
			if (Numeric::AreEqual(velBInA.GetY(), 0.0f)) {
				isSeparateY = BCenterInA.GetY() < ALeftY || BCenterInA.GetY() > ARightY;
			}
			else {
				// vel x not equals to 0
				float tClose = (ALeftY - BCenterInA.GetY()) / velBInA.GetY();
				float tOpen = (ARightY - BCenterInA.GetY()) / velBInA.GetY();
				if (tClose > tOpen) {
					float temp = tClose;
					tClose = tOpen;
					tOpen = temp;
				}
				isSeparateY = tOpen < 0 || tClose > nextFrameTime;
				if (tClose > lastCloseTime) lastCloseTime = tClose;
				if (tOpen < firstOpenTime) firstOpenTime = tOpen;
			}
			if (isSeparateY)
				return;
		
		if (lastCloseTime > firstOpenTime)
			return;
		// Collide
	}
private:
	vector<WeakPtr<Collider>> m_Colliders;
};

