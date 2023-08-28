#pragma once
#include "Object.h"

#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace lady
{
	class Actor : public Object
	{
	public:
		CLASS_DECLARATION(Actor)

		Actor() = default;

		Actor(const lady::Transform& transform) :
			transformg{ transform }
		{}

		Actor(const Actor& other);
		virtual ~Actor() {
			OnDestroy();
		}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float dt);
		virtual void Draw(lady::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);


		template<typename T>
		T* GetComponent();

		float GetRadius() { return 7.5f; }

		virtual void OnCollisionEnter(Actor* other) {}
		virtual void OnCollisionExit(Actor* other) {}

		class Scene* m_scene = nullptr;

		friend class Scene;
		
		class Game* m_game = nullptr;

		float m_lifespan = -1.0f;

	public:
		Transform transformg;
		inline float Wrap(float value, float max)
		{
			return std::fmod(value, max) + ((value < 0) ? max : 0);
		}
		std::string tag;
		bool persistent = false;
		bool prototype = false;
		bool m_destroyed = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}
