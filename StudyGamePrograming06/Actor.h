#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,		//稼働中
		EPaused,		//更新停止中
		EDead			//削除対象
	};

	Actor(class Game* game);
	virtual ~Actor();

	// ゲームから呼び出される更新関数(オーバーライド不可)
	void Update(float deltaTime);
	// アクターが持つ全コンポーネントを更新(オーバーライド不可)
	void UpdateComponents(float deltaTime);
	// アクター独自の更新処理(オーバーライド可能)
	virtual void UpdateActor(float deltaTime);
	// ゲームから呼び出されるProcess Input(オーバーライド不可)
	void ProcessInput(const uint8_t* keyState);
	// アクター独自の入力処理(オーバーライド可能)
	virtual void ActorInput(const uint8_t* keyState);

	// ゲッター・セッター
	// 位置
	const Vector3& GetPosition() const { return mPosition; }
	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true;}
	// 拡大率（質量は変えない。半径に影響する）
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; mRecomputeWorldTransform = true;}
	// 回転
	const Quaternion& GetRotation() const { return mRotation; }
	void SetRotation(const Quaternion& rotation) { mRotation = rotation; mRecomputeWorldTransform = true;}
	// 半径
	float GetRadius() { return mRadius * mScale; }	//拡大率を考慮
	void SetRadius(float radius) { mRadius = radius; mRecomputeWorldTransform = true;}
	

	// ワールド変換
	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	// 向きの単位ベクトル
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }		//向きの単位ベクトル

	// 状態
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// アクターの状態
	State mState;

	// 移動
	Vector3 mPosition;		//画面上の位置(３次元）
	float mScale;			//拡大率
	Quaternion mRotation;		//回転（クォータニオン）
	float mRadius;			//半径（拡大率は無視）
	
	// 変換
	Matrix4 mWorldTransform;
	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;
	class Game* mGame;
};
