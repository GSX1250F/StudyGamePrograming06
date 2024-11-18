#include "MeshActors.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Renderer.h"
#include "Actor.h"

MeshActors::MeshActors(Game* game)
{
	Actor* a;
	std::string meshfile;
	// サイコロ
	meshfile = "Assets/Dice.gpmesh";
	a = new Dice(game, meshfile);		// BasicMesh
	a->SetPosition(Vector3(500.0f, -200.0f, 0.0f));
	a->SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(a);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice.gpmesh"));
	MoveComponent* m = new MoveComponent(a);

	a = new Dice2(game);		// LambertMesh

	a = new Dice3(game);		// PhongMesh

	// 球
	a = new Sphere(this);		// BasicMesh
	a = new Sphere2(this);		// LambertMesh
	a = new Sphere3(this);		// PhongMesh

	// レーシングカー
	a = new RacingCar(this);		// BasicMesh
	a = new RacingCar2(this);		// LambertMesh
	a = new RacingCar3(this);		// PhongMesh

	// 壁と床
	a = new Plane(this);		// PhongMesh

}

Dice::Dice(Game* game) :Actor(game)
{
	SetPosition(Vector3(500.0f, -200.0f, 0.0f));
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice.gpmesh"));
	mMoveComp = new MoveComponent(this);
}



Dice::Dice(Game* game, std::string meshfile) : Actor(game)
{
}

void Dice::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector3 axis = Vector3::Normalize(Vector3(1.0f, -1.0f, 1.0f));
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