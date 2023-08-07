#pragma once
#include "PhysicsComponent.h"

namespace kiko
{
	class EnginePhysicsComponet : public PhysicsComponent
	{
	public:
		virtual void Update(float dt) override;
		void ApplyForce(const vec2& force) override;

	};
}