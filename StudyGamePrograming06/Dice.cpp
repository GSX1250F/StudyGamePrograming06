#include "Dice.h"
#include "MeshComponent.h"
#include "Game.h"
#include "Renderer.h"

Dice::Dice(Game* game) :Actor(game)
{
	SetPosition(Vector3(75.0f, 200.0f, 0.0f));
	SetScale(100.0f);
	Quaternion q(Vector3::UnitY, -0.5f * Math::Pi);	//yŽ²’†S‚É-90‹‰ñ‚·
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, -0.75f * Math::Pi));		//‚³‚ç‚ÉzŽ²’†S‚É-135‹‰ñ‚·
	SetRotation(q);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Dice.gpmesh"));
}
