#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	void EnginePhysicsComponet::Update(float dt)
	{
		m_owner->m_transform.position += m_velocity * dt;
		m_velocity += std::pow(1.0f - m_damping, dt);
	}
	void EnginePhysicsComponet::ApplyForce(const vec2& force)
	{

	}
}
