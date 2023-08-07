#pragma once
#include "FrameWork/Actor.h"

class Player : public kiko::Actor
{
public:
	Player(float speed, float turnRate, float health, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_health{ health }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 0;
};
