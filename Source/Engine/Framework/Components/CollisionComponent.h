#pragma once
#include "Component.h"

namespace kiko
{
	class CollisionComponent : public Component
	{
	public:
		virtual bool CheckCollide(CollisionComponent* collision) = 0;

	public:
		float m_radius = 0;

	};
}