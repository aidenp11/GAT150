#pragma once
#include "FrameWork/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace lady
{
	class Enemy : public lady::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

		Enemy() = default;
		Enemy(float speed, float health, const lady::Transform& transform) :
			Actor{ transform },
			speed{ speed }
		{}

		bool Initialize() override;
		void Update(float dt) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;


		lady::PhysicsComponent* m_physicsComponent = nullptr;
	};
}
