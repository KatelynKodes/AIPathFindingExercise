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
    Collectable(float x, float y, float maxSpeed, float maxForce, int color, Maze* maze);

    bool getCollected() { return m_collected; }
    void setCollected(bool value) { m_collected = value; }

    void setTarget(Actor* target);
    Actor* getTarget() { return m_target; }

    bool EnemyInRange();

    void start() override;
    void update(float deltaTime) override;

    void onCollision(Actor* other) override;

private:
    PathfindComponent* m_pathFindComponent;
    WanderComponent* m_wanderComponent;
    FleeComponent* m_fleeComponent;
    SeekComponent* m_seekComponent;
    Maze* m_maze;
    Actor* m_target;
    
    bool m_collected;
    float m_seekRange = 100;
};

