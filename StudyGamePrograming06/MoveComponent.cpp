#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) 
	: Component(owner), 
	mMoveForce(Vector2::Zero),
	mMoveAccel(Vector2::Zero),
	mRotForce(0.0f),
	mRotAccel(0.0f),
	mMoveResist(0.0f),
	mRotResist(0.0f)
{
	
}

MoveComponent::~MoveComponent()
{
}

void MoveComponent::Update(float deltatime)
{
	// Actor�̏d�S���x�Ɖ�]���x���X�V
	// Actor�̈ʒu�Ɗp�x��Actor��Update�ōX�V
	if (!Math::NearZero(mOwner->GetMass())) {
		mMoveAccel = mMoveForce * (1.0f / mOwner->GetMass());	//�d�S�����x�̌v�Z�@F=ma  a=F*(1/m)
		//��R�� = ����*��R�W��    ���� = -����*��R�W��/����
		Vector3 movedecel = mOwner->GetVelocity() * mMoveResist *0.01f * (1 / mOwner->GetMass());
		mMoveAccel -= movedecel;
	}
	else { mMoveAccel = Vector3::Zero; }
	if (!Math::NearZero(mOwner->GetImoment()) && !Math::NearZero::(mOwner->GetRadius())) {
		mRotAccel = mRotForce * mOwner->GetRadius() / mOwner->GetImoment();	//��]�����x�̌v�Z Fr=Ia  a=Fr/I
		//��R�� = ����*��R�W��    ���� = -����*��R�W��*���a/�������[�����g
		float rotdecel = mOwner->GetRotSpeed() * mOwner->GetRadius() * mRotResist / mOwner->GetImoment();
		mRotAccel -= rotdecel;
	}
	else { mRotAccel = 0; }
	mOwner->SetVelocity(mOwner->GetVelocity() + mMoveAccel * deltatime);	//v = vo + at
	mOwner->SetRotSpeed(mOwner->GetRotSpeed() + mRotAccel * deltatime);		//�� = ��o + ��t
}
