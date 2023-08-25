#include "fungame.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Framework/Event/EventManager.h"
#include <functional>


bool FunGame::Initialize()
{
	lady::g_audioSystem.AddAudio("hit", "Audio/Laser_Shoot.wav");

	m_scene = std::make_unique<lady::Scene>();
	m_scene->Load("Scenes/platformerscene.json");
	m_scene->Initialize();

	lady::EventManager::Instance().Subscribe("AddPoint", this, std::bind(&FunGame::AddPoint, this, std::placeholders::_1));
	lady::EventManager::Instance().Subscribe("OnPlayerDead", this, std::bind(&FunGame::OnPlayerDead, this, std::placeholders::_1));

	return true;
}

void FunGame::Shutdown()
{
}


void FunGame::Update(float dt)
{
	switch (m_state)
	{
	case FunGame::eState::Title:
		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
		}
		break;
	case FunGame::eState::StartGame:


		break;
	case FunGame::eState::StartLevel:
	






	
	break;
	case FunGame::eState::Game:


		break;
	case FunGame::eState::PlayerDead:
		
		break;
	case FunGame::eState::GameOVer:

	
		break;
	default:
		break;
	}

	m_scene->Update(dt);
}

void FunGame::Draw(lady::Renderer& renderer)
{
	m_scene->Draw(renderer);
	
}

void FunGame::AddPoint(const lady::Event& event)
{
	m_score += std::get<int>(event.data);
}

void FunGame::OnPlayerDead(const lady::Event& event)
{
	m_lives--;
	m_state = eState::PlayerDead;
}
