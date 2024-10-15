#pragma once
#include "Actor.h"
class RacingCar : public Actor
{
public:
	RacingCar(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

