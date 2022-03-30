#pragma once
#include "Agent.h"

class Maze;
class PathfindComponent;
class SeekComponent;
class WanderComponent;
class FleeComponent;
class StateMachineComponent;

class Collectable :
    public Agent
{
public:
    /// <summary>
    /// The basse Collectable constructor, calls the Agent constructor and sets it's
    /// position, name, maxforce and maxSpeed
    /// </summary>
    /// <param name="x"></param>
    /// <param name="y"></param>
    /// <param name="maxSpeed"></param>
    /// <param name="maxForce"></param>
    /// <param name="color"></param>
    /// <param name="maze"></param>
    Collectable(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze);
    
    /// <summary>
    /// The deconstructor for the collectable object
    /// </summary>
    ~Collectable();

    /// <summary>
    /// Shows whether the collectable object has been collected or not
    /// </summary>
    /// <returns> the value of m_collected </returns>
    bool getCollected() { return m_collected; }

    /// <summary>
    /// Sets the Collectable object to be collected or not collected
    /// </summary>
    /// <param name="value"> the value to set m_collected to </param>
    void setCollected(bool value) { m_collected = value; }

    /// <summary>
    /// Returns if the collectable is dead or not.
    /// </summary>
    /// <returns> value of m_isDead</returns>
    bool getDead() { return m_isDead; }

    /// <summary>
    /// Sets the collectable to be dead or alive
    /// </summary>
    /// <param name="value"> the value to set m_isDead to</param>
    void setDead(bool value) { m_isDead = value; }

    /// <summary>
    /// Sets the target of the collectable
    /// </summary>
    /// <param name="target"> the target to set m_target to be</param>
    void setTarget(Actor* target);

    /// <summary>
    /// returns the collectable's current target
    /// </summary>
    /// <returns> the value of m_target </returns>
    Actor* getTarget() { return m_target; }

    /// <summary>
    /// Checks if the enemy is in range or not
    /// </summary>
    /// <returns> True if enemy is in range of the collectable, false if not.</returns>
    bool EnemyInRange();

    void start() override;
    void update(float deltaTime) override;

    /// <summary>
    /// A method checking what the collectable collides with and performs certain actions
    /// depending on what it collides with. 
    /// </summary>
    /// <param name="other"> The actor the collectable collides with</param>
    void onCollision(Actor* other) override;

private:
    PathfindComponent* m_pathFindComponent;
    WanderComponent* m_wanderComponent;
    FleeComponent* m_fleeComponent;
    SeekComponent* m_seekComponent;
    Maze* m_maze;
    Actor* m_target;
    
    bool m_collected = false;
    bool m_isDead = false;
    float m_seekRange = 100;
};

