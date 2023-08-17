#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
	CLASS_DEFINITION(EnginePhysicsComponet)

	void EnginePhysicsComponet::Update(float dt)
	{
		m_owner->transformg.position += m_velocity * dt;
		m_velocity += std::pow(1.0f - m_damping, dt);
	}
	void EnginePhysicsComponet::ApplyForce(const vec2& force)
	{

	}

	void EnginePhysicsComponet::Read(const json_t& value)
	{

	}
}
