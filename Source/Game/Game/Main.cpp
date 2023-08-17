#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Player.h"
#include "Enemy.h"
#include "Audio/AudioSystem.h"
#include "SpaceGame.h"
#include "Framework/Framework.h"
#include <iostream>
#include <vector>
#include <thread>
#include <array>
#include <map>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2& pos, const kiko::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update() 
	{
		m_pos += m_vel * 10 * kiko::g_time.GetDeltaTime();
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};

inline std::ostream& operator<<(std::ostream& stream, const kiko::Vector2& v)
{
	stream << v.x << " " << v.y;
	return stream;
}

int main(int argc, char* argv[])
{
	INFO_LOG("program is running");

	kiko::MemoryTracker::Initialize();

	kiko::seedRandom((unsigned int)time(nullptr));
	kiko::setFilePath("assets");

	int* p = new int;
	delete p;

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC196", 800, 600);

	kiko::g_inputSystem.Initialize();
	kiko::g_audioSystem.Initialize();

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	std::shared_ptr<kiko::Model> m_model; 

	vector<Star> stars;
	for (int i = 0; i < 300; i++)
	{
		kiko::Vector2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		kiko::Vector2 vel(kiko::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();

		kiko::g_audioSystem.PlayOneShot("music", true);
		
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		game->Update(kiko::g_time.GetDeltaTime());

			if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
				!kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
			{
				kiko::g_audioSystem.PlayOneShot("hit", false);
			}
		
		
		
		kiko::g_particleSystem.Update(kiko::g_time.GetDeltaTime());
		kiko::g_renderer.SetColor(0, 0, 0, 0);

		kiko::g_renderer.BeginFrame();

		kiko::Vector2 vel(1.0f, 1.0f);

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x >= kiko::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= kiko::g_renderer.GetHeight()) star.m_pos.y = 0;

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			kiko::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);

		} 
		game->Draw(kiko::g_renderer);
		
		kiko::g_renderer.EndFrame();
	}

	return 0;
}
