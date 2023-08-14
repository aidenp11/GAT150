#include "Player.h"
#include "Input/InputSystem.h"
#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"

bool Player::Initialize()
{
	Actor::Initialize(); 
	
	// cache off
	m_physicsComponent = GetComponent<kiko::PhysicsComponent>();
	auto collisionComponent = GetComponent<kiko::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<kiko::RenderComponent>();
		if (renderComponent)
		{
			float scale = m_transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;
		}
	}

	return true;
}

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	m_physicsComponent->ApplyForce(forward * m_speed * thrust); 


	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		kiko::Transform transform { m_transform.position - 10, m_transform.rotation, 0.5f };

		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 500.0f, transform );
		std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
		component->m_texture = GET_RESOURCE(kiko::Texture, "rocket.png", kiko::g_renderer);
		weapon->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		weapon->AddComponent(std::move(collisionComponent));

		weapon->m_tag = "PlayerBullet";
		m_scene->Add(std::move(weapon));
	}
}

void Player::OnCollision(Actor* other)
{
	
		if (other->m_tag == "EnemyBullet")
		{
			m_health -= 1;
		}

		if (other->m_tag == "SpeedUp")
		{
			m_speed += 0.10f;
		}
		if (m_health == 0)
		{
			m_game->SetLives(m_game->GetLives() - 1);
			m_destroyed = true;
			kiko::g_audioSystem.PlayOneShot("explosion", false);
			dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
		}
}


