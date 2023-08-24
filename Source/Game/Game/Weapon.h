#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace lady
{
	class Weapon : public Actor
	{

	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float dt) override;
		void OnCollisionEnter(Actor* other);

	private:
		float speed = 0;
	public:

		Weapon() = default;
		lady::PhysicsComponent* m_physicsComponent = nullptr;
	};
}

