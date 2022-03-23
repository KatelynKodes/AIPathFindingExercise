#pragma once
#include "Agent.h"
#include "Collectable.h"

class Maze;
class PathfindComponent;

class Ghost : public Agent
{
public:
	/// <param name="x">The x-position</param>
	/// <param name="y">The y-position</param>
	/// <param name="speed">The maximum movement speed (magnitude)</param>
	/// <param name="color">The color in 0xRRGGBBAA</param>
	/// <param name="maze">The maze used for pathfinding</param>
	Ghost(float x, float y, float speed, float maxForce, int color, Maze* maze);
	~Ghost();

	virtual void update(float deltaTime) override;
	virtual void draw() override;

	virtual void onCollision(Actor* other) override;

	/// <returns>The current target</returns>
	Actor* getTarget();
	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget(Actor* target);

	/// <summary>
	/// Set the target of the ghost
	/// </summary>
	/// <param name="target">The new target</param>
	void setTarget();

	void setCollectables(DynamicArray<Collectable*> collectableList);
	DynamicArray<Collectable*> getCollectables() { return m_collectables; }

private:
	PathfindComponent* m_pathfindComponent;
	Maze* m_maze;
	Actor* m_target = nullptr;
	DynamicArray<Collectable*> m_collectables;
};

