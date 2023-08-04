#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace kiko
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const kiko::Transform& transform, std::shared_ptr<Model> model) :
			m_transform{ transform },
			m_model{ model }
		{}

		Actor(const kiko::Transform& transform) :
			m_transform{ transform }
		{}

		virtual void Update(float dt);
		virtual void Draw(kiko::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return (m_model) ? m_model->GetRadius() * m_transform.scale : 0; }

		virtual void OnCollision(Actor* other) {}

		class Scene* m_scene = nullptr;

		friend class Scene;
		
		class Game* m_game = nullptr;

		float m_lifespan = -1.0f;

		kiko::Transform m_transform;
		inline float Wrap(float value, float max)
		{
			return std::fmod(value, max) + ((value < 0) ? max : 0);
		}
		std::string m_tag;

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		bool m_destroyed = false;
		

		std::shared_ptr<Model> m_model;
	};
}
