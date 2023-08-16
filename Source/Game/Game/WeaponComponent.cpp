#include "WeaponComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace kiko
{
	bool WeaponComponent::Initialize()
	{
		auto collisionComponent = m_owner->GetComponent<kiko::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = m_owner->GetComponent<kiko::RenderComponent>();
			if (renderComponent)
			{
				float scale = m_owner->transformg.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;
			}
		}

		return true;
	}

	void WeaponComponent::Update(float dt)
	{
		kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_owner->transformg.rotation);
		m_owner->transformg.position += forward * speed * kiko::g_time.GetDeltaTime();
		m_owner->transformg.position.x = kiko::Wrap(m_owner->transformg.position.x, (float)kiko::g_renderer.GetWidth());
		m_owner->transformg.position.y = kiko::Wrap(m_owner->transformg.position.y, (float)kiko::g_renderer.GetHeight());
	}

	void WeaponComponent::OnCollision(Actor* other)
	{
		/*if (other->m_tag != m_owner->m_tag)
		{
			m_owner->m_destroyed = true;
		}*/
	}
	void WeaponComponent::Read(const json_t& value)
	{
		READ_DATA(value, speed);
	}
}
