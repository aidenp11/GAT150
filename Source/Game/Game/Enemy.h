#pragma once
#include "FrameWork/Actor.h"

class Enemy : public kiko::Actor
{
public:
	Enemy(float speed, float turnRate, float health, const kiko::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate },
		m_health{ health }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
	float m_health = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};
