#include "Emitter.h"
#include "Renderer/Particle.h"
#include "Renderer/ParticleSystem.h"

void kiko::Emitter::Update(float dt)
{
	Actor::Update(dt);
	
	if (m_data.burst)
	{
		m_data.burst = false;
		for (int i = 0; i < m_data.burstCount; i++)
		{
			Emit();
		}
	}
	
	if (m_data.spawnRate > 0.0f)
	{
		m_data.spawnRateTimer += dt;
		while (m_data.spawnRateTimer > 0)
		{
			Emit();
			m_data.spawnRateTimer -= (1 / m_data.spawnRate);
		}
	}
}

void kiko::Emitter::Draw(kiko::Renderer& renderer)
{

}

void kiko::Emitter::Emit()
{
	Particle* particle = g_particleSystem.GetFreeParticle();
	if (particle)
	{
		ParticleData data;
		data.lifetime = randomf(m_data.lifetimeMin, m_data.lifetimeMax);
		data.lifetimer = 0.0f;
		data.position = transformg.position;
		data.prevPosition = data.position;
		data.color = m_data.color;
		float angle = transformg.rotation + m_data.angle + randomf(-
			m_data.angleRange, m_data.angleRange);
		vec2 direction = vec2{ 0, -1 }.Rotate(angle);
		data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
		data.damping = m_data.damping;
		particle->Initialize(data);
	}
}
