#pragma once
#include "PhysicsComponent.h"

namespace lady
{
	class EnginePhysicsComponet : public PhysicsComponent
	{
	public:
		CLASS_DECLARATION(EnginePhysicsComponet)

		virtual void Update(float dt) override;
		void ApplyForce(const vec2& force) override;

	};
}