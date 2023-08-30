#pragma once
#include "FrameWork/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace lady
{
	class Player : public lady::Actor
	{
	public:
		CLASS_DECLARATION(Player)

			Player() = default;
			Player(float speed, float jump, float health, const lady::Transform& transform) :
			Actor{ transform },
			speed{ speed },
			jump{ jump }
		{}

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;

		lady::PhysicsComponent* m_physicsComponent = nullptr;
		class AnimComponent* m_animComponent = nullptr;
	};
}

