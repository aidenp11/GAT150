#pragma once
#include "CollisionComponent.h"

namespace lady
{

	class CircleCollisionComponent : public CollisionComponent
	{
	public:
		CLASS_DECLARATION(CircleCollisionComponent)

		void Update(float dt) override;
		bool CheckCollide(CollisionComponent* collision) override;
	};
}
