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

	auto collisionComponent = GetComponent<lady::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<lady::RenderComponent>();
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
		lady::Vector2 direction = player->transformg.position - transformg.position;
		transformg.rotation = direction.Angle() + lady::halfpi;
	}

	lady::vec2 forward = lady::vec2{ 0, -1 }.Rotate(transformg.rotation);
	transformg.position += forward * m_speed * lady::g_time.GetDeltaTime();
	transformg.position.x = lady::Wrap(transformg.position.x, (float)lady::g_renderer.GetWidth());
	transformg.position.y = lady::Wrap(transformg.position.y, (float)lady::g_renderer.GetHeight());

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

void Enemy::OnCollisionEnter(Actor* other)
{
	if (other->tag == "PlayerBullet")
	{
		m_health -= 1;
	}
	if (m_health <= 0)
	{
		m_destroyed = true;
		lady::g_audioSystem.PlayOneShot("explosion", false);
		lady::EventManager::Instance().DispatchEvent("AddPoints", 100);
		m_game->AddPoint(lady::random(150));
	}
}
