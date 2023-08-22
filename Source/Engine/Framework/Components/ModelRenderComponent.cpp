#include "ModelRenderComponent.h"
#include "Framework/Actor.h"
#include "Framework/Framework.h"

namespace lady
{
	CLASS_DEFINITION(ModelRenderComponent)

	bool ModelRenderComponent::Initialize()
	{
		if (!modelName.empty()) m_model = GET_RESOURCE(Model, modelName);
		return true;
	}
	void ModelRenderComponent::Update(float dt)
	{
	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->transformg);
	}

	void ModelRenderComponent::Read(const json_t& value)
	{
		READ_DATA(value, modelName);
	}
}
