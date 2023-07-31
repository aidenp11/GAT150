#pragma once
#include "Renderer.h"
#include "Core/Core.h"

struct ParticleData
{
	kiko::vec2 position;
	kiko::vec2 prevPosition;
	kiko::vec2 velocity;
	float damping = 0;
	kiko::Color color;
	float lifetimer = 0;
	float lifetime = 0;
};

namespace kiko {
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
