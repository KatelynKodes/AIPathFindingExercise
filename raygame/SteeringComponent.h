#pragma once
#include "Component.h"
#include <Vector2.h>
class Actor;
class Agent;

class SteeringComponent :
	public Component
{
public:
	SteeringComponent() { m_target = nullptr; m_steeringForce = 0; };
	SteeringComponent(Actor* actor, float steeringForce) { m_target = actor; m_steeringForce = steeringForce; }

	virtual MathLibrary::Vector2 calculateForce() = 0;

	/// <summary>
	/// Returns the steering force of the steering Component
	/// </summary>
	/// <returns> the value of m_steeringForce</returns>
	float getSteeringForce() { return m_steeringForce; }

	/// <summary>
	/// Sets the steering force of the steering component
	/// </summary>
	/// <param name="steeringForce"> the value to set the steering force to </param>
	void setSteeringForce(float steeringForce) { m_steeringForce = steeringForce; }

	/// <summary>
	/// Returns the target of the steering component
	/// </summary>
	/// <returns> the value of m_target </returns>
	Actor* getTarget() { return m_target; }

	/// <summary>
	/// Set the target of the steering component.
	/// </summary>
	/// <param name="target"> the value to set the steering component's target to</param>
	void setTarget(Actor* target) { m_target = target; }

	/// <summary>
	/// Gets the owner of the component
	/// </summary>
	/// <returns>the value getOwner() returns casted as an agent</returns>
	Agent* getAgent() { return (Agent*)getOwner(); }

private:
	float m_steeringForce = 0;
	Actor* m_target = nullptr;
};

