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
	m_physicsComponent = GetComponent<lady::PhysicsComponent>();
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

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	//transformg.rotation += rotate * m_turnRate * lady::g_time.GetDeltaTime();
	m_physicsComponent->ApplyTorque(rotate * m_turnRate);

	float thrust = 0;
	if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	lady::vec2 forward = lady::vec2{ 0, -1 }.Rotate(transformg.rotation);
	//transformg.position += forward * m_speed * thrust * lady::g_time.GetDeltaTime();
	transformg.position.x = lady::Wrap(transformg.position.x, (float)lady::g_renderer.GetWidth());
	transformg.position.y = lady::Wrap(transformg.position.y, (float)lady::g_renderer.GetHeight());

	m_physicsComponent->ApplyForce(forward * m_speed * thrust); 


	if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
		!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket");
		weapon->transformg = { transformg.position, transformg.rotation, 0.5f };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
//		kiko::Transform transform { transformg.position - 10, transformg.rotation, 0.5f };
//
//		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 500.0f, transform );
//		std::unique_ptr<kiko::SpriteComponent> component = std::make_unique<kiko::SpriteComponent>();
//		component->m_texture = GET_RESOURCE(kiko::Texture, "rocket.png", kiko::g_renderer);
//		weapon->AddComponent(std::move(component));
//
//		auto collisionComponent = std::make_unique<kiko::CircleCollisionComponent>();
//		collisionComponent->m_radius = 30.0f;
//		weapon->AddComponent(std::move(collisionComponent));
//
//		weapon->tag = "PlayerBullet";
//		m_scene->Add(std::move(weapon));
	}
}

void Player::OnCollisionEnter(Actor* other)
{
	
		if (other->tag == "EnemyBullet")
		{
			m_health -= 1;
		}

		if (other->tag == "SpeedUp")
		{
			m_speed += 0.10f;
		}
		if (m_health == 0)
		{
			//m_game->SetLives(m_game->GetLives() - 1);
			lady::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
			m_destroyed = true;
			lady::g_audioSystem.PlayOneShot("explosion", false);
			//dynamic_cast<SpaceGame*>(m_game)->SetState(SpaceGame::eState::PlayerDead);
		}
}


