#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponet : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponet)

		virtual void Update(float dt) override;
		void ApplyForce(const vec2& force) override;

	};
}