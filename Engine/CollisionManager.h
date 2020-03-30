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
		Matrix4x4 mAToWorld = mRot * mTrans;
		Matrix4x4 mWorldToA = mAToWorld.getInverse();
		mRot = Matrix4x4::CreateZRotation(B.GetRotRad());
		mTrans = Matrix4x4::CreateTranslation(B.GetPosition());
		Matrix4x4 mBToWorld = mRot * mTrans;
		Matrix4x4 mWorldToB = mBToWorld.getInverse();

		Matrix4x4 mAToB = mWorldToB * mAToWorld;
		Matrix4x4 mBToA = mAToB.getInverse();

		// Check A to B
		Vector4 projAToB_x = mAToB * Vector4(l->Size.x, 0, 0, 0);
		Vector4 projAToB_y = mAToB * Vector4(0, l->Size.y, 0, 0);
		Vector4 ACenterInB = mAToB * Vector3(l->Center);
		// x axis
		float lengthProjAOntoB_x = fabs(projAToB_x.GetX()) + fabs(projAToB_y.GetX());
		bool isSeparateX = fabs(ACenterInB.GetX() - r->Center.x) > (lengthProjAOntoB_x + r->Size.x);
		if (isSeparateX) 
			return;
		// y axis
		float lengthProjAOntoB_y = fabs(projAToB_x.GetY()) + fabs(projAToB_y.GetY());
		bool isSeparateY = fabs(ACenterInB.GetY() - r->Center.y) > (lengthProjAOntoB_y + r->Size.y);
		if (isSeparateY) 
			return;

		// Check B to A
		Vector4 projBToA_x = mBToA * Vector4(r->Size.x, 0, 0, 0);
		Vector4 projBToA_y = mBToA * Vector4(0, r->Size.y, 0, 0);
		Vector4 BCenterInA = mBToA * Vector3(r->Center);
		// x axis
		float lengthProjBOntoA_x = fabs(projBToA_x.GetX()) + fabs(projBToA_y.GetX());
		isSeparateX = fabs(BCenterInA.GetX() - l->Center.x) > (lengthProjBOntoA_x + l->Size.x);
		if (isSeparateX) 
			return;
		// y axis
		float lengthProjBOntoA_y = fabs(projBToA_x.GetY()) + fabs(projBToA_y.GetY());
		isSeparateY = fabs(BCenterInA.GetY() - l->Center.y) > (lengthProjBOntoA_y + l->Size.y);
		if (isSeparateY) 
			return;
		// Collide
	}
private:
	vector<WeakPtr<Collider>> m_Colliders;
};

