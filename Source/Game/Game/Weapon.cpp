#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace lady
{
	CLASS_DEFINITION(Weapon)

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<lady::PhysicsComponent>();

		auto collisionComponent = GetComponent<lady::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<lady::RenderComponent>();
			if (renderComponent)
			{
				float scale = transformg.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void Weapon::Update(float dt)
	{
		Actor::Update(dt);

		lady::vec2 forward = lady::vec2{ 0, -1 }.Rotate(transformg.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

		/*transformg.position += forward * speed * lady::g_time.GetDeltaTime();*/
		transformg.position.x = lady::Wrap(transformg.position.x, (float)lady::g_renderer.GetWidth());
		transformg.position.y = lady::Wrap(transformg.position.y, (float)lady::g_renderer.GetHeight());
	}

	void Weapon::OnCollisionEnter(Actor* other)
	{
		/*if (other->m_tag != m_tag)
		{
			m_destroyed = true;
		}*/
	}
	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}
