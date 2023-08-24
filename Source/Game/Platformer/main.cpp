#include "fungame.h"
#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"
#include "Physics/PhysicsSystem.h"
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>
#include <functional>

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("program is running");

	lady::MemoryTracker::Initialize();

	lady::seedRandom((unsigned int)time(nullptr));
	lady::setFilePath("assets");

	int* p = new int;
	delete p;

	lady::g_renderer.Initialize();
	lady::g_renderer.CreateWindow("CSC196", 800, 600);

	lady::g_inputSystem.Initialize();
	lady::g_audioSystem.Initialize();
	lady::PhysicsSystem::Instance().Initialize();

	unique_ptr<FunGame> game = make_unique<FunGame>();
	game->Initialize();

	std::shared_ptr<lady::Model> m_model;

	bool quit = false;
	while (!quit)
	{
		lady::g_time.Tick();
		lady::g_inputSystem.Update();

		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		game->Update(lady::g_time.GetDeltaTime());

		if (lady::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!lady::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			lady::g_audioSystem.PlayOneShot("hit", false);
		}



		lady::g_particleSystem.Update(lady::g_time.GetDeltaTime());
		lady::PhysicsSystem::Instance().Update(lady::g_time.GetDeltaTime());
		lady::g_renderer.SetColor(0, 0, 0, 0);

		lady::g_renderer.BeginFrame();
		game->Draw(lady::g_renderer);

		lady::g_renderer.EndFrame();
	}

	return 0;
}
