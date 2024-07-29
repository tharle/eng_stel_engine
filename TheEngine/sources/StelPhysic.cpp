#include <StelPhysic.h>
#include <math.h>
#include "StelEntity.h"


bool StelPhysic::CheckPointCircle(StelPointF point, StelCircleF circle)
{
    float vecX = point.x - circle.x;
    float vecY = point.y - circle.y;
    float d = sqrtf((vecX * vecX) + (vecY * vecY));

    return d <= circle.radius;
}

bool StelPhysic::CheckCircles(StelCircleF c1, StelCircleF c2)
{
    float vecX = c1.x - c2.x;
    float vecY = c1.y - c2.y;
    float d = sqrtf((vecX * vecX) + (vecY * vecY));

    return d <= (c1.radius + c2.radius);
}

bool StelPhysic::CheckPointRect(StelPointF point, StelRectF rect)
{
    return point.x >= rect.x && point.y >= rect.y && point.x <= (rect.x + rect.w) && point.y <= (rect.y + rect.h);
}

bool StelPhysic::CheckRects(StelRectF r1, StelRectF r2)
{
    return (r1.x <= (r2.x + r2.w) && (r1.x + r1.w) >= r2.x &&
        r1.y <= (r2.y + r2.h) && (r1.y + r1.h) >= r2.y);
}

bool StelPhysic::CheckRectCircle(StelRectF rect, StelCircleF circle)
{
    if (CheckPointRect({ circle.x, circle.y }, rect))
    {
        return true;
    }

    float tx = circle.x;
    float ty = circle.y;

    if (tx < rect.x) tx = rect.x;
    if (tx > rect.x + rect.w) tx = rect.x + rect.w;
    if (ty < rect.y) ty = rect.y;
    if (ty > rect.y + rect.h) ty = rect.y + rect.h;

    return CheckPointCircle({ tx, ty }, circle);
}

void StelPhysic::AddToLayer(const std::string& layerName, StelEntity* entity)
{
    if (m_Layers.count(layerName) == 0)
    {
        m_Layers.emplace(layerName, std::vector<StelEntity*>());
    }

    m_Layers[layerName].push_back(entity);
}

StelEntity* StelPhysic::CollideWithLayer(StelEntity* entity, const std::string& layerName)
{
    if (m_Layers.count(layerName) > 0)
    {
        StelRectF entityCollider = entity->GetTransform().GetTrueRect();

        for (StelEntity* entityInLayer : m_Layers[layerName])
        {
            if (entity == entityInLayer) continue;

            StelRectF entityInLayerColldier = entityInLayer->GetTransform().GetTrueRect();

            if (CheckRects(entityCollider, entityInLayerColldier))
            {
                return entityInLayer;
            }
        }
    }

    return nullptr;
}

void StelPhysic::Remove(StelEntity* entity)
{
    for (auto layer : m_Layers)
    {
        std::vector<StelEntity*>::iterator it = layer.second.begin();
        while (it != layer.second.end())
        {
            if (*it == entity)
            {
                layer.second.erase(it);
                return;
            }

            it++;
        }
    }
}