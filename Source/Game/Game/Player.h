#pragma once
#include "FrameWork/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, float health, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_health{ health }
	{}

	bool Initialize() override;
	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 0;

	kiko::PhysicsComponent* m_physicsComponent = nullptr;
};
