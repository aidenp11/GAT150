#pragma once
#include "Framework/Game.h"
#include "Renderer/Text.h"
#include "Framework/Emitter.h"
#include "Framework/Event/EventManager.h"

class SpaceGame : public lady::Game, lady::IEventListener
{
public:
	enum class eState
	{
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOVer
	};

public:
	virtual bool Initialize() override;

	virtual void Shutdown() override;

	virtual void Update(float dt) override;

	virtual void Draw(lady::Renderer& renderer) override;

	void AddPoint(const lady::Event& event);

	void OnPlayerDead(const lady::Event& event);

	void SetState(eState state) { m_state = state; }

private:
	eState m_state = eState::Title;
	float m_spawnTimer = 0;
	float m_spawnTime = 3;
	float m_stateTimer = 0;

	std::shared_ptr<lady::Font> m_font;
	std::unique_ptr<lady::Text> m_scoreText;
	std::unique_ptr<lady::Text> m_titleText;
	std::unique_ptr<lady::Text> m_gameOverText;

};
