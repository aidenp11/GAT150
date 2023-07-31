#include "ModelManager.h"

namespace kiko
{
	ModelManager g_mmanager;

	std::shared_ptr<Model> ModelManager::Get(const std::string& filename)
	{
		if (m_model.find(filename) == m_model.end())
		{
			std::shared_ptr<Model> model = std::make_shared<Model>();
			model->Load(filename);

			m_model[filename] = model;
		}

		return m_model[filename];
	}
}