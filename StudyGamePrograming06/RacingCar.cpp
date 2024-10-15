#include "RacingCar.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"

RacingCar::RacingCar(Game* game) :Actor(game)
{
	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	SetScale(1.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	mMoveComp = new MoveComponent(this);
}

void RacingCar::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3(1.0f, -1.0f, 1.0f);
	axis.Normalize();
	float rotSpeedMax = 100.0f * Math::Pi;
	float rotSpeed = rotSpeedMax * deltaTime;
	Vector3 v = rotSpeed * axis;
	mMoveComp->SetRotSpeed(v);
}
