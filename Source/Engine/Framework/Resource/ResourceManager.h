#pragma once
#include "Resource.h"
#include <map>
#include <memory>
#include <string>

namespace kiko
{
	class ResourceManager
	{
	public:
		template<typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& filename, TArgs ... args);

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;

	};

	template<typename T, typename ...TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& filename, TArgs ...args)
	{
		if (m_resources.find(filename) != m_resources.end()) 
		{
			return std::dynamic_pointer_cast<T>(m_resources[filename]); 
		}

		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->Create(filename, ...);
		m_resources[filename] = resource;

		return resource;
	}
}