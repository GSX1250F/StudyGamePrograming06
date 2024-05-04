#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//�R���X�g���N�^�BUpdate Order�͑��߁B
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Update���I�[�o�[���C�h
	void Update(float deltatime) override;

	// �ÓT�����������B�d�S�ɂ�����͂Ɖ�]�ɂ�����͂̃Z�b�^�[��p��
	void SetMoveForce(Vector3 forceV) { mMoveForce = forceV; }
	void SetRotForce(Quaternion forceQ) { mRotForce = forceQ; }
	void SetMoveResist(float resist) { mMoveResist = resist; }
	void SetRotResist(float resist) { mRotResist = resist; }

protected:


private:
	// �d�S�ɂ������
	Vector3 mMoveForce;
	// ��]�����̗�F�@ �g���N=RotForce * Radius = Imoment * RotAccel
	Quaternion mRotForce;
	// �d�S�����x
	Vector3 mMoveAccel;
	// ��]�����x
	Quaternion mRotAccel;
	
	// �d�S���x��R��(%)
	float mMoveResist;
	// ��]���x��R��(%)
	float mRotResist;


};

