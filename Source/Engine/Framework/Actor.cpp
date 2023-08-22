#include "Actor.h"
#include "Components/RenderComponent.h"

namespace lady
{
	CLASS_DEFINITION(Actor)

	Actor::Actor(const Actor& other)
	{
		name = other.name;
		tag = other.tag;
		m_lifespan = other.m_lifespan;
		m_destroyed = other.m_destroyed;
		transformg = other.transformg;
		m_scene = other.m_scene;
		m_game = other.m_game;

		for (auto& component : other.components)
		{
			auto cloneComponent = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(cloneComponent));
		}
	}

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}

	void Actor::Update(float dt)
	{
		if (m_lifespan != -1.0f && !m_destroyed)
		{
			m_lifespan -= dt;
			m_destroyed = (m_lifespan <= 0);
		}

		for (auto& component : components)
		{
			component->Update(dt);
		}
	}

	void Actor::Draw(lady::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_transform);
		for (auto& component : components)
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, m_lifespan);
		READ_DATA(value, persistent);
		READ_DATA(value, prototype);

		if (HAS_DATA(value, transform)) transformg.Read(GET_DATA(value, transform));

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;

				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);
				AddComponent(std::move(component));
			}
		}
	}
}