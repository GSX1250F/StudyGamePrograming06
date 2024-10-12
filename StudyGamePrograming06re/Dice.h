#pragma once
#include "Actor.h"
class Dice : public Actor
{
public:
	Dice(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

