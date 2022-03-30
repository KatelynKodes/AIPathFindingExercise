#pragma once
#include "SteeringComponent.h"
class FleeComponent :
	public SteeringComponent
{
public:
	/// <summary>
	/// Calculates the seek force of the owner
	/// </summary>
	/// <returns> a vector 2 containing the seekforce</returns>
	MathLibrary::Vector2 calculateForce() override;
};

