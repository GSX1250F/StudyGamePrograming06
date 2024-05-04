#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mState(EActive),
	mPosition(Vector3::Zero),
	mVelocity(Vector3::Zero),
	mScale(1.0f),
	mRotation(Quaternion::Identity),
	mRotSpeed(Quaternion::Identity),
	mMass(1.0f),
	mRadius(0.0f),
	mGame(game),
	mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	// ~ComponentではRemoveActorが呼び出されるので、別の種類のループを使う
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive || mState == EPaused)	// EPausedのときも更新するよう修正。
	{
		// ワールド変換
		ComputeWorldTransform();

		// 位置情報を更新
 		SetPosition(GetPosition() + mVelocity * deltaTime);

		Quaternion rot = GetRotation();
		float angle = mRotSpeed * deltaTime;
		// 回転を追加させるクォータニオンを作成
		// (+X軸周りの回転）
		Quaternion inc(Vector3::UnitX, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		// (+Y軸周りの回転）
		Quaternion inc(Vector3::UnitY, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		// (+Z軸周りの回転）
		Quaternion inc(Vector3::UnitZ, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		// ワールド変換（再変換）
		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

//新しく追加されたインプット用関数
void Actor::ProcessInput(const uint8_t* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

//機能追加するときオーバーライドするインプット用関数
void Actor::ActorInput(const uint8_t* keyState)
{
}

float Actor::GetImoment()
{
	//Actorの慣性モーメントを設定。一様密度の球とする。(I=2/5*mR^2)
	float mImoment = 0.4f * GetMass() * GetRadius() * GetRadius();
	return mImoment;
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// まずスケーリング、次に回転、最後に平行移動
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		// ワールド変換の更新をコンポーネントに通知する
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}


void Actor::AddComponent(Component* component)
{
	// ソート済みの配列で挿入点を見つける
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// イテレータの位置の前に要素を挿入する
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}