#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	bool Weapon::Initialize()
	{
		auto collisionComponent = GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<kiko::RenderComponent>();
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
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(transformg.rotation);
		transformg.position += forward * speed * kiko::g_time.GetDeltaTime();
		transformg.position.x = kiko::Wrap(transformg.position.x, (float)kiko::g_renderer.GetWidth());
		transformg.position.y = kiko::Wrap(transformg.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void Weapon::OnCollision(Actor* other)
	{
		/*if (other->m_tag != m_tag)
		{
			m_destroyed = true;
		}*/
	}
	void Weapon::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}
}
