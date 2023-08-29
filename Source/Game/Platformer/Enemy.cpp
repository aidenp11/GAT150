#include "Enemy.h"
#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"

namespace lady
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();


		return true;
	}

	void Enemy::Update(float dt)
	{
		Actor::Update(dt);

		vec2 forward = vec2{ 0, -1 }.Rotate(transformg.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			vec2 direction = player->transformg.position - transformg.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{
		

	}

	void Enemy::OnCollisionExit(Actor* other)
	{
		
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}


