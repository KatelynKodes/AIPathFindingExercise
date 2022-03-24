#include "Collectable.h"
#include "MazeScene.h"
#include "Wall.h"
#include "raylib.h"
#include "Transform2D.h"
#include "AABBCollider.h"
#include "PathfindComponent.h"
#include "MoveComponent.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "FleeComponent.h"
#include "SpriteComponent.h"
#include "StateMachineComponent.h"

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

	m_fleeComponent = new FleeComponent();
	m_fleeComponent->setSteeringForce(500);
	addComponent(m_fleeComponent);

	m_wanderComponent = new WanderComponent(5, 5, 500);
	addComponent(m_wanderComponent);

	m_seekComponent = new SeekComponent();
	m_seekComponent->setSteeringForce(500);
	addComponent(m_seekComponent);

	//Add the sprite component
	addComponent(new SpriteComponent("Images/enemy.png"));
}

Collectable::~Collectable()
{
	delete m_fleeComponent;
	delete m_pathFindComponent;
	delete m_seekComponent;
	Actor::~Actor();
}

void Collectable::setTarget(Actor* target)
{
	m_target = target;
}

bool Collectable::EnemyInRange()
{
	if (!getTarget())
		return false;

	MathLibrary::Vector2 targetPos = getTarget()->getTransform()->getWorldPosition();
	MathLibrary::Vector2 ownerPos = getTransform()->getWorldPosition();
	float distanceFromTarget = (targetPos - ownerPos).getMagnitude();
	bool targetInRange = distanceFromTarget <= m_seekRange;

	return targetInRange;
}

void Collectable::start()
{
	Agent::start();

	//Add the state machine components
	addComponent<StateMachineComponent>();
	getComponent<StateMachineComponent>()->setCurrentState(WANDER); //Set the current state to wander
	getComponent<StateMachineComponent>()->start(); //Call start function

	//set collider for the collectable so it can be collided with
	setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, this));
}

void Collectable::update(float deltaTime)
{
	Agent::update(deltaTime);

	bool enemyInRange = EnemyInRange();
	bool collected = getCollected();

	if (m_isdead)
	{
		getComponent<StateMachineComponent>()->setCurrentState(DEAD);
	}
	else
	{
		if (enemyInRange && !collected)
		{
			getComponent<FleeComponent>()->setTarget(getTarget());
			getComponent<StateMachineComponent>()->setCurrentState(FLEE);
		}
		else
		{
			if (collected)
			{
				getComponent<SeekComponent>()->setTarget(m_target);
				getComponent<StateMachineComponent>()->setCurrentState(SEEK);
			}
			else
			{
				getComponent<StateMachineComponent>()->setCurrentState(WANDER);
			}
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
}
