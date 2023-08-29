#include "BoxPhysicsComponent.h"
#include "Framework/Actor.h"
#include <box2d/include/box2d/box2d.h>
#include "Physics/PhysicsSystem.h"

namespace lady
{
	CLASS_DEFINITION(BoxPhysicsComponent)

		bool BoxPhysicsComponent::Initialize()
	{
		m_body = PhysicsSystem::Instance().CreateBody(m_owner->transformg.position, m_owner->transformg.rotation, data);
		m_body->SetGravityScale(data.gravityScale);
		m_body->SetLinearDamping(data.damping);
		m_body->SetAngularDamping(data.angularDamping);

		return true;
	}

	void BoxPhysicsComponent::OnDestroy()
	{
		if (m_body)
		{
			m_body->SetEnabled(false);
			PhysicsSystem::Instance().DestroyBody(m_body);
		}
	}

	void BoxPhysicsComponent::Update(float dt)
	{
		Vector2 position = B2VEC2_TO_VEC2(m_body->GetPosition());
		m_owner->transformg.position = PhysicsSystem::Instance().WorldToScreen(position);
		m_owner->transformg.rotation = m_body->GetAngle();
		m_velocity = B2VEC2_TO_VEC2(m_body->GetLinearVelocity());
	}

	void BoxPhysicsComponent::ApplyForce(const vec2& force)
	{
		m_body->ApplyForceToCenter(VEC2_TO_B2VEC2(force), true);
	}

	void BoxPhysicsComponent::ApplyTorque(float torque)
	{
		m_body->ApplyTorque(torque, true);
	}

	void BoxPhysicsComponent::SetVelocity(const vec2& velocity)
	{
		m_body->SetLinearVelocity(VEC2_TO_B2VEC2(velocity));
	}

	void BoxPhysicsComponent::Read(const json_t& value)
	{
		READ_NAME_DATA(value, "damping", data.damping);
		READ_NAME_DATA(value, "angularDamping", data.angularDamping);
		READ_NAME_DATA(value, "gravityScale", data.gravityScale);
		READ_NAME_DATA(value, "constrainAngle", data.constrainAngle);
		READ_NAME_DATA(value, "isDynamic", data.isDynamic);
	}
}