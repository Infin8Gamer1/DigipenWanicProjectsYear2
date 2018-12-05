#include "stdafx.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics.h"
#include "Animation.h"
#include "Collider.h"
#include "Sprite.h"
#include "Space.h"

Behaviors::Enemy::Enemy() : Component("Enemy")
{
	currentState = EnemyStates::StateIdle;  // The current state of the enemy. Ex: idle, wander, chase
	nextState = EnemyStates::StateIdle;		// The next state of the enemy.

	wanderDirection = EnemyWanderDirections::Jump; //the direction to wander
	previousWanderDirection = EnemyWanderDirections::Jump; //the direction to wander

	innerState = InnerStates::InnerStateEnter; // The inner state of the current state. Ex: enter, update, exit

	timer = 0; // Used for delaying state changes, etc.
	stateChangeTime = -1; // Amount of time to wait before changing states.
}

Component * Behaviors::Enemy::Clone() const
{
	return new Enemy(*this);
}

void Behaviors::Enemy::Initialize()
{
	//get Components
	transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
	physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	animation = static_cast<Animation*>(GetOwner()->GetComponent("Animation"));
	sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
	//set the collision handler for the Enemy
	static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(EnemyMapCollisionHandler);
}

void Behaviors::Enemy::Update(float dt)
{
	switch (currentState)
	{
		case StateIdle:
		{
			switch (innerState)
			{
				case InnerStateEnter:
					innerState = InnerStateUpdate;
					//reset timer
					timer = 0;
					animation->Play(0, 0, 0.1f, true);
					break;
				case InnerStateUpdate:
					//Idle for 1 second then go back to wander state
					if (timer > 1.0f) {
						Vector2D translation = static_cast<Transform*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Monkey")->GetComponent("Transform"))->GetTranslation();
						if (translation.Distance(transform->GetTranslation()) > 400) {
							innerState = InnerStateExit;
							SetState(EnemyStates::StateWander);
						}
						else {
							innerState = InnerStateExit;
							SetState(EnemyStates::StateChase);
						}	
					}
					break;
				case InnerStateExit:
					currentState = nextState;
					innerState = InnerStateEnter;
					break;
			}
			break;
		}

		case StateWander:
		{
			switch (innerState)
			{
				case InnerStateEnter:
					while (wanderDirection == previousWanderDirection) {
						wanderDirection = static_cast<EnemyWanderDirections>(rand() % EnemyWanderDirections::Last);
					}
					//reset timer
					timer = 0;
					//play animation baised on direction
					switch (wanderDirection)
					{
						case Behaviors::Left:
							animation->Play(2, 5, 0.1f, true);
							break;
						case Behaviors::Right:
							animation->Play(2, 5, 0.1f, true, true);
							break;
						case Behaviors::Jump:
							animation->Play(1, 1, 0.1f, true);
							break;
					}
					sprite->SetColor(normalColor);
					innerState = InnerStateUpdate;
					break;
				case InnerStateUpdate:
					// Wandering behavior movement
					switch (wanderDirection)
					{
						case Behaviors::Left:
							physics->SetVelocity(Vector2D(150, 0));
							break;
						case Behaviors::Right:
							physics->SetVelocity(Vector2D(-150, 0));
							break;
						case Behaviors::Jump:
							physics->AddForce(Vector2D(0, 250.0f));
							break;
					}

					//do this for 2 seconds then go back to idle
					if (timer > 2.0f) {
						innerState = InnerStateExit;
						SetState(EnemyStates::StateIdle);
					}
					break;
				case InnerStateExit:
					previousWanderDirection = wanderDirection;
					physics->SetVelocity(Vector2D(0, 0));

					currentState = nextState;
					innerState = InnerStateEnter;
					break;
			}
			break;
		}
			

		case StateChase:
		{
			switch (innerState)
			{
				case InnerStateEnter:
					sprite->SetColor(madColor);
					innerState = InnerStateUpdate;
					timer = 0;
					break;
				case InnerStateUpdate:
					// TO DO: Chasing behavior
					if (timer > 5.0f) {
						innerState = InnerStateExit;
						SetState(EnemyStates::StateIdle);
					}
					
					break;
				case InnerStateExit:
					currentState = nextState;
					innerState = InnerStateEnter;
					break;
			}
			break;
		}
	}

	timer += dt;
}

void Behaviors::Enemy::SetState(EnemyStates _nextState)
{
	nextState = _nextState;
}

void Behaviors::EnemyMapCollisionHandler(GameObject & object, const MapCollision & collision)
{
	static_cast<Enemy*>(object.GetComponent("Enemy"))->onWallRight = collision.right;
	static_cast<Enemy*>(object.GetComponent("Enemy"))->onWallLeft = collision.left;
	static_cast<Enemy*>(object.GetComponent("Enemy"))->onGround = collision.bottom;
}
