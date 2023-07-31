#include "SpaceGame.h"
#include "Framework/Game.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Renderer/Text.h"
#include "Renderer/Font.h"
#include "Framework/Emitter.h"
#include "Renderer/ParticleSystem.h"
#include "SpeedUp.h"


bool SpaceGame::Initialize()
{
	m_font = std::make_shared<kiko::Font>("BodoniFLF-Bold.ttf", 24);

	m_scoreText = std::make_unique<kiko::Text>(m_font);
	m_titleText = std::make_unique<kiko::Text>(m_font);
	m_gameOverText = std::make_unique<kiko::Text>(m_font);
	
	kiko::g_audioSystem.AddAudio("hit", "Laser_Shoot.wav");
	kiko::g_audioSystem.AddAudio("explosion", "Explosion.wav");
	kiko::g_audioSystem.AddAudio("music", "spacesong.wav");

	m_scene = std::make_unique<kiko::Scene>();

	m_scoreText->Create(kiko::g_renderer, "SCORE: 00000", kiko::Color{ 0, 0, 0, 0 } );
	m_titleText->Create(kiko::g_renderer, "SPACE GAME!", kiko::Color{ 1, 1, 1, 1 } );
	m_gameOverText->Create(kiko::g_renderer, "GAME OVER!", kiko::Color{ 1, 0, 0, 1 });

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
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
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

		std::unique_ptr<Player> player = std::make_unique<Player>(100.0f, kiko::pi, 500.0f, kiko::Transform{ { 400.0f, 300.0f }, 0.0f, 4.0f }, kiko::g_mmanager.Get("Ship.txt"));
		player->m_tag = "Player";
		player->m_game = this;
		m_scene->Add(std::move(player));

		m_state = eState::Game;
	}
		break;
	case SpaceGame::eState::Game:
		m_spawnTimer += dt;
		if (m_spawnTimer >= m_spawnTime)
		{
			m_spawnTimer = 0;
			std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(kiko::randomf(25.0f, 50.0f), kiko::pi, kiko::randomf(50.0f, 200.0f), kiko::Transform{ { kiko::randomf(600.0f), kiko::randomf(400.0f) }, kiko::randomf(kiko::pi), 3.0f}, kiko::g_mmanager.Get("EnemyShip.txt"));
			enemy->m_tag = "Enemy";
			enemy->m_game = this;
			m_scene->Add(std::move(enemy));
			spawnAmount++;

		} 
		if (spawnAmount == 3)
		{
			std::unique_ptr<SpeedUp> speedUp = std::make_unique<SpeedUp>(10.0f, kiko::randomf(25.0f, 50.0f), kiko::Transform{ { kiko::randomf(600.0f), kiko::randomf(400.0f) }, kiko::randomf(kiko::pi), 3.0f}, kiko::g_mmanager.Get("SpeedUp.txt"));
			speedUp->m_tag = "SpeedUp";
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
			data.angleRange = kiko::pi;
			data.lifetimeMin = 0.5f;
			data.lifetimeMin = 1.5f;
			data.speedMin = 50;
			data.speedMax = 250;
			data.damping = 0.5f;
			data.color = kiko::Color{ 1, 1, 1, 1 };
			kiko::Transform transform{ { kiko::g_inputSystem.GetMousePosition() }, 0.0f, 1.0f };
			auto emitter = std::make_unique<kiko::Emitter>(transform, data);
			emitter->m_lifespan = 1.0f;
			if (kiko::g_inputSystem.GetMouseButtonDown(0)) {
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

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && 
			!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::Title;
		}
		break;
	default:
		break;
	}

	m_scoreText->Create(kiko::g_renderer, std::to_string(m_score), { 1, 1, 1, 1 } );
	m_scene->Update(dt);
}

void SpaceGame::Draw(kiko::Renderer& renderer)
{
	if (m_state == eState::Title)
	{
		m_titleText->Draw(renderer, 400, 300);
	}

	if (m_state == eState::GameOVer)
	{
		m_gameOverText->Draw(renderer, 400, 300);
	}

	m_scoreText->Draw(renderer, 40, 20);
	kiko::g_particleSystem.Draw(renderer);
	m_scene->Draw(renderer);
}
