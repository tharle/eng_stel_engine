#pragma once
#include <string>

class StelEntity;
struct StelPointF;
struct StelCircleF;
struct StelRectF;

class IPhysic
{
public:
    virtual ~IPhysic() = default;

    virtual bool CheckPointCircle(StelPointF point, StelCircleF circle) = 0;
    virtual bool CheckCircles(StelCircleF c1, StelCircleF c2) = 0;
    virtual bool CheckPointRect(StelPointF point, StelRectF rect) = 0;
    virtual bool CheckRects(StelRectF r1, StelRectF r2) = 0;
    virtual bool CheckRectCircle(StelRectF rect, StelCircleF circle) = 0;

    virtual void AddToLayer(const std::string& layerName, StelEntity* entity) = 0;
    virtual bool CollideWithLayer(StelEntity* entity, const std::string& layerName, StelEntity** other) = 0;
    virtual void Remove(StelEntity* entity) = 0;
};