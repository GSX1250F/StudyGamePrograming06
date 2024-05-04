#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
public:
	//コンストラクタ。Update Orderは早め。
	MoveComponent(class Actor* owner , int updateOrder = 10);
	~MoveComponent();

	//Updateをオーバーライド
	void Update(float deltatime) override;

	// 古典物理を実装。重心にかかる力と回転にかかる力のセッターを用意
	void SetMoveForce(Vector3 forceV) { mMoveForce = forceV; }
	void SetRotForce(Quaternion forceQ) { mRotForce = forceQ; }
	void SetMoveResist(float resist) { mMoveResist = resist; }
	void SetRotResist(float resist) { mRotResist = resist; }

protected:


private:
	// 重心にかかる力
	Vector3 mMoveForce;
	// 回転方向の力F　 トルク=RotForce * Radius = Imoment * RotAccel
	Quaternion mRotForce;
	// 重心加速度
	Vector3 mMoveAccel;
	// 回転加速度
	Quaternion mRotAccel;
	
	// 重心速度抵抗率(%)
	float mMoveResist;
	// 回転速度抵抗率(%)
	float mRotResist;


};

