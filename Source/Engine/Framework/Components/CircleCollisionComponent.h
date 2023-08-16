#pragma once
#include "CollisionComponent.h"

namespace kiko
{

	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponent)

		void Update(float dt) override;
		bool CheckCollide(CollisionComponent* collision) override;
	};
}
