#include "SpeedUp.h"
#include "Player.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

void SpeedUp::Update(float dt)
{
	Actor::Update(dt);

	m_transform.rotation += m_turnRate * kiko::g_time.GetDeltaTime();

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());
}

void SpeedUp::OnCollision(Actor* other)
{
	if (other->m_tag == "PlayerBullet")
	{
		m_destroyed = true;
	}
}
