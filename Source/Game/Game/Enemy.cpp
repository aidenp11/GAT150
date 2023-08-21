#include "Enemy.h"
#include "Player.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "SpaceGame.h"
#include "Framework/Emitter.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"

bool Enemy::Initialize()
{
	Actor::Initialize();

	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = transformg.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;
}

void Enemy::Update(float dt)
{
	Actor::Update(dt);

	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		kiko::Vector2 direction = player->transformg.position - transformg.position;
		transformg.rotation = direction.Angle() + kiko::halfpi;
	}

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transformg.rotation);
	transformg.position += forward * m_speed * kiko::g_time.GetDeltaTime();
	transformg.position.x = kiko::Wrap(transformg.position.x, (float)kiko::g_renderer.GetWidth());
	transformg.position.y = kiko::Wrap(transformg.position.y, (float)kiko::g_renderer.GetHeight());

	/*m_fireTimer -= dt;
	if (m_fireTimer <= 0)
	{
		kiko::Transform transform { transformg.position, transformg.rotation, 0.3f };
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(200.0f, transformg);
		weapon->tag = "EnemyBullet";
		m_scene->Add(std::move(weapon));
		m_fireTimer = m_fireRate;
	}*/
}

void Enemy::OnCollision(Actor* other)
{
	if (other->tag == "PlayerBullet")
	{
		m_health -= 1;
	}
	if (m_health <= 0)
	{
		m_destroyed = true;
		kiko::g_audioSystem.PlayOneShot("explosion", false);
		m_game->AddPoint(kiko::random(150));
	}
}
