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
#include <functional>

using namespace std;

class Star
{
public:
	Star(const lady::Vector2& pos, const lady::Vector2& vel) :
		m_pos{ pos },
		m_vel{ vel }
	{}

	void Update() 
	{
		m_pos += m_vel * 10 * lady::g_time.GetDeltaTime();
	}

public:
	lady::Vector2 m_pos;
	lady::Vector2 m_vel;
};

inline std::ostream& operator<<(std::ostream& stream, const lady::Vector2& v)
{
	stream << v.x << " " << v.y;
	return stream;
}

void print(int i)
{
	cout << i << endl;
}

int add(int i1, int i2)
{
	return i1 + i2;
}

int sub(int i1, int i2)
{
	return i1 - i2;
}

class A
{
public:
	int add(int i1, int i2)
	{
		return i1 + i2;
	}
};

union Data
{
	int i;
	bool b;
	char c[6];
};

int main(int argc, char* argv[])
{
	Data data;
	data.i = 0;
	cout << data.b << endl;

	void (*func_ptr)(int) = &print;
	func_ptr(5);

	int (*op_ptr)(int, int);
	op_ptr = add;
	
	cout << op_ptr(4, 4) << endl;

	std::function<int(int, int)> op;
	op = add;
	cout << op(5, 6) << endl;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	cout << op(6, 6) << endl;

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

	unique_ptr<SpaceGame> game = make_unique<SpaceGame>();
	game->Initialize();

	std::shared_ptr<lady::Model> m_model; 

	vector<Star> stars;
	for (int i = 0; i < 300; i++)
	{
		lady::Vector2 pos(lady::random(lady::g_renderer.GetWidth()), lady::random(lady::g_renderer.GetHeight()));
		lady::Vector2 vel(lady::randomf(1, 4), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	bool quit = false;
	while (!quit)
	{
		lady::g_time.Tick();
		lady::g_inputSystem.Update();
		lady::g_audioSystem.Update();

		lady::g_audioSystem.PlayOneShot("music", true);
		
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
		lady::g_renderer.SetColor(0, 0, 0, 0);

		lady::g_renderer.BeginFrame();
		game->Draw(lady::g_renderer);

		for (auto& star : stars)
		{
			star.Update();

			if (star.m_pos.x >= lady::g_renderer.GetWidth()) star.m_pos.x = 0;
			if (star.m_pos.y >= lady::g_renderer.GetHeight()) star.m_pos.y = 0;

			lady::g_renderer.SetColor(lady::random(256), lady::random(256), lady::random(256), 255);
			lady::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);

		} 
		
		lady::g_renderer.EndFrame();
	}

	return 0;
}
