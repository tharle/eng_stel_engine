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

class StelTilemap : public StelComponent, public IDrawable
{
public:
    virtual ~StelTilemap() = default;
    StelTilemap();
    StelTilemap(StelEntity* parent);

    virtual void Draw() override;

    void Load(const std::string& filename, int mapW, int mapH, int tileW, int tileH);
    void AddLayer(const std::string& layer, TLayer tiles);
    TLayer GetLayer(const std::string& name);
    bool IsColliding(const std::string& layer, float x, float y, float w, float h, int* tileIndex);

private:
    TTilemap m_Tilemap;
    int m_Width = 0;
    int m_Height = 0;
    size_t m_TilesetId = 0;
    int m_TileWidth = 0;
    int m_TileHeight = 0;
    TTileset m_Tileset;
    int m_ScaleFactor = 1;
};