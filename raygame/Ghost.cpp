#include "Ghost.h"
#include "MazeScene.h"
#include "Engine.h"
#include "Wall.h"
#include "raylib.h"
#include "Transform2D.h"
#include "AABBCollider.h"
#include "PathfindComponent.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Player.h"
#include "Collectable.h"

Ghost::Ghost(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze)
	: Agent(x, y, "Ghost", maxSpeed, maxForce)
{
	m_maze = maze;
	getTransform()->setScale({ Maze::TILE_SIZE,Maze::TILE_SIZE });

	m_pathfindComponent = new PathfindComponent(maze);
	m_pathfindComponent->setColor(color);
	addComponent(m_pathfindComponent);
	addComponent(new SpriteComponent("Images/enemy.png"));

	//set collider for the collectable so it can be collided with
	setCollider(new AABBCollider(Maze::TILE_SIZE, Maze::TILE_SIZE, this));
}

Ghost::~Ghost()
{
	delete m_pathfindComponent;
	Actor:: ~Actor();
}

void Ghost::update(float deltaTime)
{
	Agent::update(deltaTime);

	//checks if the maze's collectable length is greater than the current collectables
	if (m_maze->getCollectables().getLength() != getCollectables().getLength())
	{
		//Set the collectables to be the maze's collectables
		setCollectables(m_maze->getCollectables());
	}

	// If there is no target
	if (!getTarget())
	{
		//set target
		setTarget();
	}
	else
	{
		//If the target is a collectable
		if (Collectable* target = dynamic_cast<Collectable*>(getTarget()))
		{
			//if the target is collected
			if (target->getCollected() || target->getDead())
			{
				//set a new target
				setTarget();
			}
		}
	}
}

void Ghost::draw()
{
	Agent::draw();
}

void Ghost::onCollision(Actor* other)
{
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
		// If player collectCount == 4
		if (player->getCollectCount() == 4)
		{
			// Destroy the ghost
		}
	}
	
	if (Collectable* collectable = dynamic_cast<Collectable*>(other))
	{
		if (!collectable->getCollected())
		{
			collectable->setDead(true);
		}
	}
}

void Ghost::setTarget(Actor* target)
{
	m_target = target;
	m_pathfindComponent->setTarget(m_target);
}

void Ghost::setTarget()
{
	if (getCollectables().getLength() != 0)
	{
		//randomly select an integer between 0 and the dynamic array's length
		int index = rand() % getCollectables().getLength();

		// if the collectable isn't collected...
		if (!getCollectables()[index]->getCollected() && !getCollectables()[index]->getDead())
			// set the target
			setTarget(getCollectables()[index]);
	}
}

void Ghost::setCollectables(DynamicArray<Collectable*> collectableList)
{
	m_collectables.clear();

	for (int i = 0; i < collectableList.getLength(); i++)
	{
		m_collectables.addItem(collectableList[i]);
	}

	for (int i = 0; i < getCollectables().getLength(); i++)
	{
		getCollectables()[i]->setTarget(this);
	}
}

Actor* Ghost::getTarget()
{
	return m_target;
}