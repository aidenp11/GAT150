#pragma once
#include "CollisionComponent.h"
#include "Physics/PhysicsSystem.h"
#include <functional>

namespace lady
{
	class BoxCollisionComponent : public CollisionComponent
	{
	public:
		using collisionFunction = std::function<void(Actor*)>;

	public:
		CLASS_DECLARATION(BoxCollisionComponent)

			virtual bool Initialize() override;
		virtual void Update(float dt) override;

	private:
		PhysicsSystem::CollisionData data;
		vec2 scaleOffset = vec2{ 1, 1 };
	};
}
