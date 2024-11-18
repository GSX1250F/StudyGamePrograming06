#pragma once
class MeshActors
{
public:
	MeshActors(class Game* game);
};

class Dice : public Actor
{
public:
	Dice(class Game* game, std::string meshfile);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class Plane : public Actor
{
public:
	Plane(class Game* game);
};

class RacingCar : public Actor
{
public:
	RacingCar(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};

class Sphere : public Actor
{
public:
	Sphere(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	class MoveComponent* mMoveComp;
};
