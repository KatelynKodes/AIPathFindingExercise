#pragma once
#include "Component.h"
#include "MazeScene.h"

/// <summary>
/// The states agents can pass through
/// </summary>
enum State
{
	DEAD,
	FLEE,
	WANDER,
	SEEK
};

class SeekComponent;
class WanderComponent;
class FleeComponent;
class PathfindComponent;

class StateMachineComponent :
	public Component
{
public:
	void start() override;

	/// <summary>
	/// Returns the current state of the state machine component
	/// </summary>
	/// <returns> the value of m_currentState </returns>
	State getCurrentState() { return m_currentState; }

	/// <summary>
	/// Sets the state component's current state
	/// </summary>
	/// <param name="state"> The state to set the current state to </param>
	void setCurrentState(State state) { m_currentState = state; }

	void update(float deltaTime) override;

private:
	State m_currentState;
	SeekComponent* m_seekComponent;
	WanderComponent* m_wanderComponent;
	FleeComponent* m_fleeComponent;
	PathfindComponent* m_pathfindComponent;
	float m_seekForce;
	float m_wanderForce;
	float m_fleeForce;
};

