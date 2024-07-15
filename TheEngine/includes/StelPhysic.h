#pragma once
#include "IPhysic.h"
#include <map>
#include <vector>

class StelPhysic : public IPhysic
    {
    public:
        virtual bool CheckPointCircle(StelPointF point, StelCircleF circle) override;
        virtual bool CheckCircles(StelCircleF c1, StelCircleF c2) override;
        virtual bool CheckPointRect(StelPointF point, StelRectF rect) override;
        virtual bool CheckRects(StelRectF r1, StelRectF r2) override;
        virtual bool CheckRectCircle(StelRectF rect, StelCircleF circle) override;
        virtual void AddToLayer(const std::string& layerName, StelEntity* entity) override;
        virtual bool CollideWithLayer(StelEntity* entity, const std::string& layerName, StelEntity** other) override;
        virtual void Remove(StelEntity* entity) override;

    private:
        std::map<std::string, std::vector<StelEntity*>> m_Layers;
    };