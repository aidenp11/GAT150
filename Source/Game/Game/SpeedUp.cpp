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

	transformg.rotation += m_turnRate * lady::g_time.GetDeltaTime();

	lady::vec2 forward = lady::vec2{ 0, -1 }.Rotate(transformg.rotation);
	transformg.position += forward * m_speed * lady::g_time.GetDeltaTime();
	transformg.position.x = lady::Wrap(transformg.position.x, (float)lady::g_renderer.GetWidth());
	transformg.position.y = lady::Wrap(transformg.position.y, (float)lady::g_renderer.GetHeight());
}

void SpeedUp::OnCollision(Actor* other)
{
	if (other->tag == "PlayerBullet")
	{
		m_destroyed = true;
	}
}
