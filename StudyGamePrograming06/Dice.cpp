#include "Dice.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"

Dice::Dice(Game* game) :Actor(game)
{
	SetPosition(Vector3(500.0f, -200.0f, 0.0f));
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void Dice::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3::Normalize(Vector3(1.0f, -1.0f,1.0f));
	float rotSpeedMax = 30.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	mMoveComp->SetRotSpeed(rotSpeed * axis);
}

Dice2::Dice2(Game* game) :Actor(game)
{
	SetPosition(Vector3(500.0f, 0.0f, 0.0f));
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice2.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void Dice2::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3::Normalize(Vector3(1.0f, -1.0f, 1.0f));
	float rotSpeedMax = 30.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	mMoveComp->SetRotSpeed(rotSpeed * axis);
}

Dice3::Dice3(Game* game) :Actor(game)
{
	SetPosition(Vector3(500.0f, 200.0f, 0.0f));
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice3.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void Dice3::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3::Normalize(Vector3(1.0f, -1.0f, 1.0f));
	float rotSpeedMax = 30.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	mMoveComp->SetRotSpeed(rotSpeed * axis);
}