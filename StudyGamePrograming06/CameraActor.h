#pragma once
#include "Actor.h"

class CameraActor : public Actor
{
public:
	CameraActor(class Game* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const SDL_Event& event) override;
private:
	class MoveComponent* mMoveComp;
};
