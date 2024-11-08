#include "Sphere.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"

Sphere::Sphere(Game* game) :Actor(game)
{
	SetPosition(Vector3(-500.0f, 200.0f, 0.0f));
	Quaternion q(Vector3::UnitX, Math::ToRadians(-23.5f));
	SetRotation(q);
	SetScale(5.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void Sphere::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3(0.0f, Math::Cos(Math::ToRadians(66.5f)), Math::Sin(Math::ToRadians(66.5f)));
	float rotSpeedMax = 5.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	mMoveComp->SetRotSpeed(rotSpeed * axis);
}

Sphere2::Sphere2(Game* game) :Actor(game)
{
	SetPosition(Vector3(-500.0f, -200.0f, 0.0f));
	Quaternion q(Vector3::UnitX, Math::ToRadians(-23.5f));
	SetRotation(q);
	SetScale(5.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere2.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void Sphere2::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3(0.0f, Math::Cos(Math::ToRadians(66.5f)), Math::Sin(Math::ToRadians(66.5f)));
	float rotSpeedMax = 5.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	mMoveComp->SetRotSpeed(rotSpeed * axis);
}
