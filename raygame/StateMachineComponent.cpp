#include "StateMachineComponent.h"
#include "Actor.h"
#include "SeekComponent.h"
#include "WanderComponent.h"
#include "FleeComponent.h"
#include "PathfindComponent.h"
#include "MoveComponent.h"
#include "Transform2D.h"

void StateMachineComponent::start()
{
	Component::start();

	//Get refrences to the owners steering components and stores them in seperate variables
	//Save the steering components steering forces in float variables
	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_fleeComponent = getOwner()->getComponent<FleeComponent>();
	m_fleeForce = m_fleeComponent->getSteeringForce();

	// Get a refrence to the owner's pathfinding component
	m_pathfindComponent = getOwner()->getComponent<PathfindComponent>();
}

void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);

	switch (m_currentState)
	{
	case DEAD:
		//Set the pathfind component to be disabled
		m_pathfindComponent->setEnabled(false);

		//Set the steering force of all the steering components to 0
		m_fleeComponent->setSteeringForce(0);
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(0);
		break;
	case FLEE:
		//Set the pathfind component to be disabled
		m_pathfindComponent->setEnabled(false);

		//Set the flee components steering force to the fleeforce
		m_fleeComponent->setSteeringForce(m_fleeForce);

		//Set the seek and wander components steering force to 0
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(0);
		break;
	case SEEK:
		//Set the pathfind component to be disabled
		m_pathfindComponent->setEnabled(false);

		//Set the flee components steering force to 0
		m_fleeComponent->setSteeringForce(0);

		//Set the seek components steering force to the seekforce
		m_seekComponent->setSteeringForce(m_seekForce);

		//Set the wander components steering force to 0
		m_wanderComponent->setSteeringForce(0);
		break;
	case WANDER:
		//Set the pathfind component to be disabled
		m_pathfindComponent->setEnabled(false);

		//Set the flee and seek components steering components to 0
		m_fleeComponent->setSteeringForce(0);
		m_seekComponent->setSteeringForce(0);

		//Set the wander components steering force to be the wander force.
		m_wanderComponent->setSteeringForce(m_wanderForce);
		break;
	}
}
