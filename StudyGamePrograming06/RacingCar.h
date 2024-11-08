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

class RacingCar2 : public Actor
{
public:
	RacingCar2(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class RacingCar3 : public Actor
{
public:
	RacingCar3(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};