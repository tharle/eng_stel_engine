#pragma once
#include <vector>
#include <map>
#include <string>
#include <IGfx.h>
#include <StelComponent.h>
#include <IDrawable.h>

typedef std::vector<std::vector<int>> TLayer;
typedef std::map<std::string, TLayer> TTilemap;
typedef std::vector<StelRectI> TTileset;

class StelTileMap : public StelComponent, public IDrawable
{
public:
    virtual ~StelTileMap() = default;
    StelTileMap();
    StelTileMap(StelEntity* parent);

    virtual void Draw() override;

    void Load(const std::string& filename, StelPointI mapSize, StelPointI tileSize, float scaleFactor);
    void AddLayer(const std::string& layer, TLayer tiles);
    TLayer GetLayer(const std::string& name);
    bool IsColliding(const std::string& layer, StelRectF rect, int* tileIndex);

private:
    int m_ScaleFactor = 1;
    TTilemap m_Tilemap;
    StelPointI m_MapSize = StelPointI::Zero();
    size_t m_TilesetId = 0;
    StelPointI m_TileSize = StelPointI::Zero();
    TTileset m_Tileset;
};