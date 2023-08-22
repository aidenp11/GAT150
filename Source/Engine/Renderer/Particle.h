#pragma once
#include "Core/Core.h"

struct ParticleData
{
	lady::vec2 position;
	lady::vec2 prevPosition;
	lady::vec2 velocity;
	float damping = 0;
	lady::Color color;
	float lifetimer = 0;
	float lifetime = 0;
};

namespace lady {
	class Renderer; 

	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		void Update(float dt);
		void Draw(Renderer& renderer);
		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
};
