#include "fungame.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Framework/Event/EventManager.h"
#include <functional>


bool FunGame::Initialize()
{
	lady::res_t<lady::Font> font = GET_RESOURCE(lady::Font, "Fonts/BodoniFLF-Bold.ttf", 24);

	lady::g_audioSystem.AddAudio("jump", "Audio/jump.wav");


	m_scene = std::make_unique<lady::Scene>();
	m_scene->Load("Scenes/platformerscene.json");
	m_scene->Load("Scenes/tilemap.json");
	m_scene->Load("Scenes/startgame.json");
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
	{
		FunGame::Initialize();
int numbercrates = -1;

		m_scene->GetActorByName<lady::Actor>("Title")->active = true;
		
		m_scene->GetActorByName<lady::Actor>("GameOver")->active = false;
		if (numbercrates < 0)
		{
			numbercrates++;
			auto actor = INSTANTIATE(Actor, "Crate");
			actor->transformg.position = { lady::randomf(50, 800), 300.0f};
			actor->Initialize();
			m_scene->Add(std::move(actor));
		}

		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			m_state = eState::StartGame;
			m_scene->GetActorByName<lady::Actor>("Title")->active = false;
		}
	}
		break;
	case FunGame::eState::StartGame:

		break;
	case FunGame::eState::StartLevel:

			
	
	break;
	case FunGame::eState::Game:


		break;
	case FunGame::eState::PlayerDead:
		m_state = eState::GameOVer;
	
		break;
	case FunGame::eState::GameOVer:
		m_scene->GetActorByName<lady::Actor>("GameOver")->active = true;
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
	m_state = eState::GameOVer;
}
