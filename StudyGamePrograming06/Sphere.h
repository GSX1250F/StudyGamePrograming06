#pragma once
#include "Actor.h"
class Sphere : public Actor
{
public:
	Sphere(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class Sphere2 : public Actor
{
public:
	Sphere2(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class Sphere3 : public Actor
{
public:
	Sphere3(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};