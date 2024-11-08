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

class Dice2 : public Actor
{
public:
	Dice2(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class Dice3 : public Actor
{
public:
	Dice3(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};