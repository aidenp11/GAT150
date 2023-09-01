#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Framework/Framework.h"

namespace lady
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();
		m_animComponent = GetComponent<AnimComponent>();

		return true;
	}

	void Player::Update(float dt)
	{
		Actor::Update(dt);

  		bool onGround = (groundCount > 0);
		vec2 velocity = m_physicsComponent->m_velocity;
		

		float dir = 0;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) dir = 1;

		if (dir != 0)
		{
		vec2 forward = vec2{ 1, 0 };
		velocity.x += speed * dir * ((onGround) ? 1 : 0.25f) * dt;
		velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
		m_physicsComponent->SetVelocity(velocity);

		//m_physicsComponent->ApplyForce(forward * speed * dir * ((onGround) ? 1 : 0.25f));
		}

		if (onGround &&
			g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) &&
			!g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
		{
			vec2 up = vec2{ 0, -1 };
			m_physicsComponent->SetVelocity(velocity + (up * jump));
			g_audioSystem.PlayOneShot("jump", false);
		}

		//if (velocity.y > 0) m_physicsComponent->SetGravityScale(3);
		//else m_physicsComponent->SetGravityScale(2);

		if (std::fabs(velocity.x) > 0.2f)
		{
			m_animComponent->flipH = (velocity.x < -0.1f);
			m_animComponent->SetSequence("run");
		}
		else
		{
			m_animComponent->SetSequence("idle");
		}
	}

	void Player::OnCollisionEnter(Actor* other)
	{
		if (other->tag == "Ground") 
			groundCount++;

		if (other->tag == "Enemy")
 			health--;

		if (health <= 0)
		{
			m_destroyed = true;
			EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}
		
	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") 
			groundCount--;
	}

	void Player::Read(const json_t& value)
		{
			Actor::Read(value);

			READ_DATA(value, speed);
			READ_DATA(value, maxSpeed);
			READ_DATA(value, jump);
			READ_DATA(value, health);
		}
}


