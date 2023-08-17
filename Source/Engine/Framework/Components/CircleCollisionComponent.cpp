#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
    CLASS_DEFINITION(CircleCollisionComponent)

    void CircleCollisionComponent::Update(float dt)
    {
    }

    bool CircleCollisionComponent::CheckCollide(CollisionComponent* collision)
    {
        float distance = m_owner->transformg.position.distance(collision->m_owner->transformg.position);
        float radius = m_radius + collision->m_radius;
        
        if (distance <= radius) return true;

        return false;
    }

    void CircleCollisionComponent::Read(const json_t& value)
    {
    
    }
}
