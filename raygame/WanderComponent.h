#pragma once
#include "SteeringComponent.h"
class WanderComponent :
	public SteeringComponent
{
public:
	WanderComponent() {};
	WanderComponent(float circleDistance, float circleRadius, float wanderForce);
	MathLibrary::Vector2 calculateForce() override;

	void setCircleDistance(float distance) { m_circleDistance = distance; }
	float getCircleDistance() { return m_circleDistance; }

	void setCircleRadius(float radius) { m_circleRadius = radius; }
	float getCircleRadius() { return m_circleRadius; }

private:
	float m_circleDistance = 0;
	float m_circleRadius = 0;
	float m_wanderAngle = 0;

	MathLibrary::Vector2 m_target;
	MathLibrary::Vector2 m_circlePos;
};

