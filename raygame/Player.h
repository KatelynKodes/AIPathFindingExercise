#pragma once
#include "Agent.h"
class InputComponent;
class MoveComponent;
class SpriteComponent;

class Player :
	public Agent
{
public:
	Player(float x, float y, const char* name, float maxForce, float maxSpeed) : Agent(x, y, name, maxForce, maxSpeed) {}

	void start() override;
	void update(float deltaTime) override;

	int getCollectCount() { return m_collectCount; }
	void setCollectCount(int value) { m_collectCount = value; }

	void onCollision(Actor* actor) override;

private:
	SpriteComponent* m_spriteComponent;
	InputComponent* m_input;
	int m_collectCount = 0;
};

