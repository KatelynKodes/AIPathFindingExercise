#include "FleeComponent.h"
#include "Actor.h"
#include "Transform2D.h"
#include "Agent.h"
#include "MoveComponent.h"

MathLibrary::Vector2 FleeComponent::calculateForce()
{
	//If getTarget is null
	if (!getTarget())
		//Return a seek force of (0,0)
		return { 0,0 };

	//Get the direction to the target
	MathLibrary::Vector2 directionToTarget = getOwner()->getTransform()->getWorldPosition() - getTarget()->getTransform()->getWorldPosition();

	//Calculate the desired velocity by getting the directionToTarget normalized multiplied by 
	//the steering force
	MathLibrary::Vector2 desriredVelocity = directionToTarget.getNormalized() * getSteeringForce();

	//Subtract the velocity in the movecomponent from the desiredVelocity to make the seekforce 
	MathLibrary::Vector2 seekForce = desriredVelocity - getAgent()->getMoveComponent()->getVelocity();

	return seekForce;
}
