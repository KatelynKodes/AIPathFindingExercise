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

	m_seekComponent = getOwner()->getComponent<SeekComponent>();
	m_seekForce = m_seekComponent->getSteeringForce();

	m_wanderComponent = getOwner()->getComponent<WanderComponent>();
	m_wanderForce = m_wanderComponent->getSteeringForce();

	m_fleeComponent = getOwner()->getComponent<FleeComponent>();
	m_fleeForce = m_fleeComponent->getSteeringForce();

	m_pathfindComponent = getOwner()->getComponent<PathfindComponent>();
}

void StateMachineComponent::update(float deltaTime)
{
	Component::update(deltaTime);

	switch (m_currentState)
	{
	case FLEE:
		m_pathfindComponent->setEnabled(false);
		m_fleeComponent->setSteeringForce(m_fleeForce);
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(0);
		break;
	case SEEK:
		m_pathfindComponent->setEnabled(false);
		m_fleeComponent->setSteeringForce(0);
		m_seekComponent->setSteeringForce(m_seekForce);
		m_wanderComponent->setSteeringForce(0);
		break;
	case WANDER:
		m_pathfindComponent->setEnabled(false);
		m_fleeComponent->setSteeringForce(0);
		m_seekComponent->setSteeringForce(0);
		m_wanderComponent->setSteeringForce(m_wanderForce);
		break;
	}
}
