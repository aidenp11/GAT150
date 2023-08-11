#pragma once
#include "CollisionComponent.h"

namespace kiko
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:



		// Inherited via CollisionComponent
		void Update(float dt) override;

		bool CheckCollide(CollisionComponent* collision) override;

	};
}
