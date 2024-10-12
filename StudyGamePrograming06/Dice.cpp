#include "Dice.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Dice::Dice(Game* game) :Actor(game)
{
	SetPosition(Vector3(75.0f, 200.0f, 0.0f));
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice.gpmesh"));
}
