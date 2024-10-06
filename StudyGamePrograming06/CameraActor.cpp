#include "CameraActor.h"
#include "MoveComponent.h"
#include "SDL_scancode.h"
#include "Renderer.h"
#include "Game.h"

CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	mMoveComp = new MoveComponent(this);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// Compute new camera from this actor
	Vector3 cameraPos = GetPosition();
	Vector3 target = GetPosition() + GetForward() * 100.0f;
	Vector3 up = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const SDL_Event& event)
{
	float forwardSpeed = 0.0f;
	float rotSpeed = 0.0f;
	// wasd movement
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP)
		{
			forwardSpeed += 300.0f;
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			forwardSpeed -= 300.0f;
		}
		if (event.key.keysym.sym == SDLK_LEFT)
		{
			rotSpeed -= Math::Pi;
		}
		if (event.key.keysym.sym == SDLK_RIGHT)
		{
			rotSpeed += Math::Pi;
		}
	}
	mMoveComp->SetVelocity(forwardSpeed * GetForward());
	mMoveComp->SetRotSpeed(rotSpeed * GetUpward());
}
