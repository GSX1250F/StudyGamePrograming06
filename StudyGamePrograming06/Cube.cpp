#include "Cube.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Cube::Cube(Game* game) :Actor(game)
{
	SetPosition(Vector3(200.0f, 75.0f, 0.0f));
	SetScale(100.0f);
	Quaternion q(Vector3::UnitY, -0.5f * Math::Pi);	//y軸中心に-90°回す
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, -0.75f * Math::Pi));		//さらにz軸中心に-135°回す
	SetRotation(q);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
}
