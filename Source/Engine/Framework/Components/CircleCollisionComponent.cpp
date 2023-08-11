#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace kiko
{
    void CircleCollisionComponent::Update(float dt)
    {
    }

    bool CircleCollisionComponent::CheckCollide(CollisionComponent* collision)
    {
        float distance = m_owner->m_transform.position.distance(collision->m_owner->m_transform.position);
        float radius = m_radius + collision->m_radius;
        
        if (distance <= radius) return true;

        return false;
    }
}
