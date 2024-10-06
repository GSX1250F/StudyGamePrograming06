#include "Sphere.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Sphere::Sphere(Game* game) :Actor(game)
{
	SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	SetScale(3.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
}
