#include "Collectable.h"
#include "MazeScene.h"
#include "Wall.h"
#include "raylib.h"
#include "Transform2D.h"
#include "PathfindComponent.h"
#include "MoveComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "FleeComponent.h"
#include "SpriteComponent.h"
#include "StateMachineComponent.h"
#include "Player.h"

Collectable::Collectable(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze):
	Agent(x,y,"Collectable", maxSpeed, maxForce)
{
	//Add a refrence to the maze
	m_maze = maze;
	//set the scale of the actor to be the size of a tile
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });

	//Add the pathfinder component
	m_pathFindComponent = new PathfindComponent(maze);
	m_pathFindComponent->setColor(color);
	addComponent(m_pathFindComponent);

	//Add the sprite component
	addComponent(new SpriteComponent("Images/enemy.png"));

	//Adding wander, flee, and seek components
	addComponent<SeekComponent>();
	addComponent<WanderComponent>();
	addComponent<FleeComponent>();
}

void Collectable::setTarget(Actor* target)
{
	m_target = target;
	m_pathFindComponent->setTarget(m_target);
}

bool Collectable::EnemyInRange()
{
	MathLibrary::Vector2 targetPos = getComponent<SeekComponent>()->getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPos = getTransform()->getWorldPosition();
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();
	bool targetInRange = distanceFromTarget <= m_seekRange;

	return targetInRange;
}

void Collectable::start()
{
	Agent::start();

	addComponent<StateMachineComponent>();
	getComponent<StateMachineComponent>()->setCurrentState(WANDER);
	getComponent<StateMachineComponent>()->start();
}

void Collectable::update(float deltaTime)
{
	Agent::update(deltaTime);

	if (EnemyInRange() && !getCollected())
	{
		getComponent<StateMachineComponent>()->setCurrentState(FLEE);
	}
	else
	{
		if (getCollected())
		{
			getComponent<StateMachineComponent>()->setCurrentState(SEEK);
		}
		else
		{
			getComponent<StateMachineComponent>()->setCurrentState(WANDER);
		}
	}

	getComponent<StateMachineComponent>()->update(deltaTime);
}

void Collectable::onCollision(Actor* other)
{
	//If the ghost runs into a wall..
	if (Wall* wall = dynamic_cast<Wall*>(other)) {
		MathLibrary::Vector2 halfTile = { Maze::TILE_SIZE / 2.0f, Maze::TILE_SIZE / 2.0f };
		MathLibrary::Vector2 position = getTransform()->getWorldPosition();
		position = position + halfTile;
		MathLibrary::Vector2 tilePosition = {
			roundf(position.x / Maze::TILE_SIZE) * Maze::TILE_SIZE,
			roundf(position.y / Maze::TILE_SIZE) * Maze::TILE_SIZE
		};
		tilePosition = tilePosition - halfTile;
		getTransform()->setWorldPostion(tilePosition);

		getMoveComponent()->setVelocity({ 0, 0 });
	}

	if (Player* player = dynamic_cast<Player*>(other))
	{
		setTarget(player);
		setCollected(true);
	}
}
