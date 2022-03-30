#pragma once
#include "SteeringComponent.h"
class WanderComponent :
	public SteeringComponent
{
public:
	WanderComponent() {};
	WanderComponent(float circleDistance, float circleRadius, float wanderForce);

	/// <summary>
	/// Calculates the steering force, an override of the base calculateForce method
	/// </summary>
	/// <returns> A vector 2 containing the value of the steering force </returns>
	MathLibrary::Vector2 calculateForce() override;

	/// <summary>
	/// Set the circle distance relative to the agent it is connected to
	/// </summary>
	/// <param name="distance"> The value the wander components circle distance will be set to </param>
	void setCircleDistance(float distance) { m_circleDistance = distance; }

	/// <summary>
	/// Returns the distance of the circle
	/// </summary>
	/// <returns> the value of m_circleDistance </returns>
	float getCircleDistance() { return m_circleDistance; }

	/// <summary>
	/// Sets the circle radius of the wander component;
	/// </summary>
	/// <param name="radius"> the value the circle radius will be set to</param>
	void setCircleRadius(float radius) { m_circleRadius = radius; }

	/// <summary>
	/// Returns the circle radius of the wander component
	/// </summary>
	/// <returns> the value of m_circleRadius </returns>
	float getCircleRadius() { return m_circleRadius; }

private:
	float m_circleDistance = 0;
	float m_circleRadius = 0;
	float m_wanderAngle = 0;

	MathLibrary::Vector2 m_target;
	MathLibrary::Vector2 m_circlePos;
};

