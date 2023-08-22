#include "SpaceGame.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "SpeedUp.h"
#include "Framework/Event/EventManager.h"
#include <functional>


bool SpaceGame::Initialize()
{
	lady::res_t<lady::Font> font = GET_RESOURCE(lady::Font, "BodoniFLF-Bold.ttf", 24);

	m_scoreText = std::make_unique<lady::Text>(font);
	//m_titleText = std::make_unique<kiko::Text>(font);
	m_gameOverText = std::make_unique<lady::Text>(font);
	
	lady::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");
	lady::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	lady::g_audioSystem.AddAudio("music", "spacesong.wav");

	m_scene = std::make_unique<lady::Scene>();
	m_scene->Load("scene.json");
	m_scene->Initialize();

	m_scoreText->Create(lady::g_renderer, "SCORE: 00000", lady::Color{ 0, 0, 0, 0 } );
	//m_titleText->Create(kiko::g_renderer, "SPACE GAME!", kiko::Color{ 1, 1, 1, 1 } );
	m_gameOverText->Create(lady::g_renderer, "GAME OVER!", lady::Color{ 1, 0, 0, 1 });

	lady::EventManager::Instance().Subscribe("AddPoint", this, std::bind(&SpaceGame::AddPoint, this, std::placeholders::_1));
	lady::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&SpaceGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void SpaceGame::Shutdown()
{
}

int spawnAmount = 0;
void SpaceGame::Update(float dt)
{
	switch (m_state)
	{
	case SpaceGame::eState::Title:
		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName<lady::Actor>("Background")->active = true;
			m_scene->GetActorByName<lady::Actor>("Title")->active = false;
		}
		break;
	case SpaceGame::eState::StartGame:
		m_score = 0;
		m_lives = 3;
		m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::StartLevel:
	{
		m_scene->RemoveAll();

		std::unique_ptr<Player> player = std::make_unique<Player>(100.0f, lady::pi, 500.0f, lady::Transform{ { 400.0f, 300.0f }, 0.0f, 1.0f });
		player->tag = "Player";
		player->m_game = this;

		// auto spriteComponent = CREATE_CLASS(SpriteComponent)

		std::unique_ptr<lady::SpriteComponent> component = std::make_unique<lady::SpriteComponent>();
		component->m_texture = GET_RESOURCE(lady::Texture, "playership.png", lady::g_renderer);
		player->AddComponent(std::move(component));

		auto physicsComponent = std::make_unique<lady::EnginePhysicsComponet>();
		physicsComponent->m_damping = 1.0f;
		player->AddComponent(std::move(physicsComponent));

		auto collisionComponent = std::make_unique<lady::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		player->AddComponent(std::move(collisionComponent));

		player->Initialize();
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(lady::randomf(25.0f, 50.0f), lady::pi, lady::randomf(50.0f, 200.0f), lady::Transform{ { lady::randomf(600.0f), lady::randomf(400.0f) }, lady::randomf(lady::pi), 1.0f});
			enemy->tag = "Enemy";
			enemy->m_game = this;

			std::unique_ptr<lady::SpriteComponent> component = std::make_unique<lady::SpriteComponent>();
			component->m_texture = GET_RESOURCE(lady::Texture, "enemyship.png", lady::g_renderer);
			enemy->AddComponent(std::move(component));

			auto collisionComponent = std::make_unique<lady::CircleCollisionComponent>();
			collisionComponent->m_radius = 30.0f;
			enemy->AddComponent(std::move(collisionComponent));

			m_scene->Add(std::move(enemy));
			spawnAmount++;

		} 
		if (spawnAmount == 3)
		{
			std::unique_ptr<SpeedUp> speedUp = std::make_unique<SpeedUp>(10.0f, lady::randomf(25.0f, 50.0f), lady::Transform{ { lady::randomf(600.0f), lady::randomf(400.0f) }, lady::randomf(lady::pi), 3.0f});
			speedUp->tag = "SpeedUp";
			speedUp->m_game = this;
			m_scene->Add(std::move(speedUp));
			spawnAmount = 0;
		}
		{
			EmitterData data;
			data.burst = true;
			data.burstCount = 100;
			data.spawnRate = 200;
			data.angle = 0;
			data.angleRange = lady::pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = lady::Color{ 1, 1, 1, 1 };
			lady::Transform transform{ { lady::g_inputSystem.GetMousePosition() }, 0.0f, 1.0f };
			auto emitter = std::make_unique<lady::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			if (lady::g_inputSystem.GetMouseButtonDown(0)) {
				m_scene->Add(std::move(emitter));
			}
		}
		break;
	case SpaceGame::eState::PlayerDead:
		if (m_lives == 0) m_state = eState::GameOVer;
		else m_state = eState::StartLevel;
		break;
	case SpaceGame::eState::GameOVer:
		
		m_scene->RemoveAll();

		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
			!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(lady::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 } );
	m_scene->Update(dt);
}

void SpaceGame::Draw(lady::Renderer& renderer)
{
	m_scene->Draw(renderer);
	if (m_state == eState::Title)
	{
		m_scene->GetActorByName<lady::Actor>("Title")->active = true;
		//m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOVer)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
	lady::g_particleSystem.Draw(renderer);
}

void SpaceGame::AddPoint(const lady::Event& event)
{
	m_score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const lady::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDead;
}
