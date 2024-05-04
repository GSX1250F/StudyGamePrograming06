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

	// ~Component�ł�RemoveActor���Ăяo�����̂ŁA�ʂ̎�ނ̃��[�v���g��
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive || mState == EPaused)	// EPaused�̂Ƃ����X�V����悤�C���B
	{
		// ���[���h�ϊ�
		ComputeWorldTransform();

		// �ʒu�����X�V
 		SetPosition(GetPosition() + mVelocity * deltaTime);

		Quaternion rot = GetRotation();
		float angle = mRotSpeed * deltaTime;
		// ��]��ǉ�������N�H�[�^�j�I�����쐬
		// (+X������̉�]�j
		Quaternion inc(Vector3::UnitX, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		// (+Y������̉�]�j
		Quaternion inc(Vector3::UnitY, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		// (+Z������̉�]�j
		Quaternion inc(Vector3::UnitZ, angle);
		rot = Quaternion::Concatenate(rot, inc);
		SetRotation(rot);
		
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		// ���[���h�ϊ��i�ĕϊ��j
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

//�V�����ǉ����ꂽ�C���v�b�g�p�֐�
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

//�@�\�ǉ�����Ƃ��I�[�o�[���C�h����C���v�b�g�p�֐�
void Actor::ActorInput(const uint8_t* keyState)
{
}

float Actor::GetImoment()
{
	//Actor�̊������[�����g��ݒ�B��l���x�̋��Ƃ���B(I=2/5*mR^2)
	float mImoment = 0.4f * GetMass() * GetRadius() * GetRadius();
	return mImoment;
}

void Actor::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// �܂��X�P�[�����O�A���ɉ�]�A�Ō�ɕ��s�ړ�
		mWorldTransform = Matrix4::CreateScale(mScale);
		mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
		mWorldTransform *= Matrix4::CreateTranslation(mPosition);

		// ���[���h�ϊ��̍X�V���R���|�[�l���g�ɒʒm����
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}


void Actor::AddComponent(Component* component)
{
	// �\�[�g�ς݂̔z��ő}���_��������
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

	// �C�e���[�^�̈ʒu�̑O�ɗv�f��}������
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