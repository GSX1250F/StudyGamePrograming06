#include "CameraActor.h"
#include "MoveComponent.h"
#include "Renderer.h"
#include "Game.h"

CameraActor::CameraActor(Game* game)
	:Actor(game)
{
	SetPosition(Vector3(-1000.0f, 0.0f, 150.0f));
	mMoveComp = new MoveComponent(this);
}

void CameraActor::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	// カメラの位置と方向を更新
	Vector3 cameraPos = GetPosition();
	Vector3 cameraTarget = GetPosition() + GetForward() * 100.0f;
	Vector3 cameraUp = Vector3::UnitZ;

	Matrix4 view = Matrix4::CreateLookAt(cameraPos, cameraTarget, cameraUp);
	GetGame()->GetRenderer()->SetViewMatrix(view);
}

void CameraActor::ActorInput(const SDL_Event& event)
{
	float forwardSpeed = 0.0f;
	float rotSpeed = 0.0f;
	if (event.type == SDL_KEYDOWN) {
		if (event.key.keysym.sym == SDLK_UP)
		{
			forwardSpeed += 500.0f;
		}
		if (event.key.keysym.sym == SDLK_DOWN)
		{
			forwardSpeed -= 500.0f;
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
