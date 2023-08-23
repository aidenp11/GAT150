#pragma once
#include "Component.h"
#include "Core/Vector.h"

namespace lady
{
	class PhysicsComponent : public Component
	{
	public: 
		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1;
		float m_damping = 0; 

	};
}