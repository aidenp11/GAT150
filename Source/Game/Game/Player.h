#pragma once
#include "FrameWork/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public lady::Actor
{
public:
	Player(float speed, float turnRate, float health, const lady::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_health{ health }
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollisionEnter(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 0;

	lady::PhysicsComponent* m_physicsComponent = nullptr;
};
