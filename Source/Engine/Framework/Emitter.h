#pragma once
#include "Core/Core.h"
#include "Actor.h"

struct EmitterData
{
	
	float spawnRate = 0;
	float spawnRateTimer = 0;
	bool burst = false;
	size_t burstCount = 0;
	
	float lifetimeMin = 0;
	float lifetimeMax = 0;
	float speedMin = 0;
	float speedMax = 0;
	float damping = 0;
	float angle = 0;
	float angleRange = 0;
	kiko::Color color;
};

namespace kiko {
	class Emitter : public Actor
	{
	public:
		Emitter() = default;
		Emitter(const Transform& transform, const EmitterData& data) :
			Actor{ transform },
			m_data{ data }
		{}
		void Update(float dt);
		void Draw(kiko::Renderer& renderer);

	private:
		void Emit();

	private:
		EmitterData m_data;
	};
};