#pragma once
#include "FrameWork/Actor.h"

class SpeedUp : public lady::Actor
{
public:
	SpeedUp(float speed, float turnRate, const lady::Transform& transform) :
		Actor{ transform },
		m_speed{ speed },
		m_turnRate{ turnRate }
	{}

	void Update(float dt) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;
};

