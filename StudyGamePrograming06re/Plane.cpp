#include "Plane.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Plane::Plane(Game* game) : Actor(game)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
}
