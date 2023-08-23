#pragma once
#include "PhysicsComponent.h"
#include "Physics/PhysicsSystem.h"

class b2Body;

namespace lady
{
	class BoxPhysicsComponent : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(BoxPhysicsComponent)

		bool Initialize() override;
		void OnDestroy() override;

		void Update(float dt) override;
		virtual void ApplyForce(const vec2& force) override;
		virtual void ApplyTorque(float torque) override;

		friend class BoxCollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body = nullptr;
	};
}
