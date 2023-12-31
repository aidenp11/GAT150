#pragma once
#include "Component.h"

namespace lady
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollide(CollisionComponent* collision) { return true; };

	public:
		float m_radius = 0;

	};
}