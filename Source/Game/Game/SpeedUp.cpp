#include "SpeedUp.h"
#include "Player.h"
#include "WeaponComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

void SpeedUp::Update(float dt)
{
	Actor::Update(dt);

	transformg.rotation += m_turnRate * kiko::g_time.GetDeltaTime();

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transformg.rotation);
	transformg.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transformg.position.x = kiko::Wrap(transformg.position.x, (float)kiko::g_renderer.GetWidth());
	transformg.position.y = kiko::Wrap(transformg.position.y, (float)kiko::g_renderer.GetHeight());
}

void SpeedUp::OnCollision(Actor* other)
{
	if (other->tag == "PlayerBullet")
	{
		m_destroyed = true;
	}
}
