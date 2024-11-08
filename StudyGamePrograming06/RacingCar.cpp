#include "RacingCar.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"

RacingCar::RacingCar(Game* game) :Actor(game)
{
	SetPosition(Vector3(500.0f, 700.0f, -100.0f));
	SetScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void RacingCar::UpdateActor(float deltaTime)
{
	float w = Math::Pi * 0.25f;
	/*
	float r = Math::Sqrt(GetPosition().x * GetPosition().x + GetPosition().y * GetPosition().y);
	float x = GetPosition().x * Math::Cos(w * deltaTime) - GetPosition().y * Math::Sin(w * deltaTime);
	float y = GetPosition().y * Math::Cos(w * deltaTime) + GetPosition().x * Math::Sin(w * deltaTime);
	SetPosition(Vector3(x, y, -100.0f));
	*/
	Quaternion q = GetRotation();
	Quaternion inc = Quaternion(Vector3::UnitZ, w * deltaTime);
	q = Quaternion::Concatenate(inc, q);
	SetRotation(q);
}

RacingCar2::RacingCar2(Game* game) :Actor(game)
{
	SetPosition(Vector3(0.0f, 700.0f, -100.0f));
	SetScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar2.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void RacingCar2::UpdateActor(float deltaTime)
{
	float w = Math::Pi * 0.25f;
	/*
	float r = Math::Sqrt(GetPosition().x * GetPosition().x + GetPosition().y * GetPosition().y);
	float x = GetPosition().x * Math::Cos(w * deltaTime) - GetPosition().y * Math::Sin(w * deltaTime);
	float y = GetPosition().y * Math::Cos(w * deltaTime) + GetPosition().x * Math::Sin(w * deltaTime);
	SetPosition(Vector3(x, y, -100.0f));
	*/
	Quaternion q = GetRotation();
	Quaternion inc = Quaternion(Vector3::UnitZ, w * deltaTime);
	q = Quaternion::Concatenate(inc, q);
	SetRotation(q);
}

RacingCar3::RacingCar3(Game* game) :Actor(game)
{
	SetPosition(Vector3(-500.0f, 700.0f, -100.0f));
	SetScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar3.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void RacingCar3::UpdateActor(float deltaTime)
{
	float w = Math::Pi * 0.25f;
	/*
	float r = Math::Sqrt(GetPosition().x * GetPosition().x + GetPosition().y * GetPosition().y);
	float x = GetPosition().x * Math::Cos(w * deltaTime) - GetPosition().y * Math::Sin(w * deltaTime);
	float y = GetPosition().y * Math::Cos(w * deltaTime) + GetPosition().x * Math::Sin(w * deltaTime);
	SetPosition(Vector3(x, y, -100.0f));
	*/
	Quaternion q = GetRotation();
	Quaternion inc = Quaternion(Vector3::UnitZ, w * deltaTime);
	q = Quaternion::Concatenate(inc, q);
	SetRotation(q);
}