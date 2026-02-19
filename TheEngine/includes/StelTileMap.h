#pragma once
#include <vector>
#include <map>
#include <string>
#include "tinyxml2.h"
#include <IGfx.h>
#include <StelComponent.h>
#include <IDrawable.h>


// Macro for check Read TMX file
#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { printf("StelTileMap->XMLCheckResult  read file error: %i\n", a_eResult); return a_eResult; }
#endif
// Check Parse
#ifndef ParseLayerCheck
#define ParseLayerCheck(layer) if (layer.empty()) { printf("StelTileMap->ParseLayerCheck  read file error: Parse to Layer Error.\n"); return tinyxml2::XML_ERROR_PARSING_TEXT; }
#endif

typedef std::vector<std::vector<int>> TLayer;
typedef std::map<std::string, TLayer> TTilemap;
typedef std::vector<TLayer> TCollider;
typedef std::vector<StelRectI> TTileset;

// Class Engine:  Read and have a collection of the tilemaps
class StelTileMap : public StelComponent, public IDrawable
{
public:
    virtual ~StelTileMap() = default;
    StelTileMap();
    StelTileMap(StelEntity* parent);

    virtual void Draw() override;

    void Load(const std::string& filename);
    void Load(const std::string& filename, StelPointI mapSize);
    void AddLayer(const std::string& layer, TLayer tiles, bool isCollider);
    tinyxml2::XMLError AddTmx(const std::string& layer);
    TLayer GetLayer(const std::string& name);
    bool IsColliding(StelRectF boxCollider, int* tileIndex);

    bool DrawColliders = false;

    const std::string TMX_TAG_MAP = "map";
    const std::string TMX_TAG_LAYER = "layer";
    const std::string TMX_TAG_COLLIDER = "collider";
    const std::string TMX_TAG_DATA = "data";
    const std::string TMX_ATT_WIDTH = "width";
    const std::string TMX_ATT_HEIGHT = "height";
    const std::string TMX_ATT_NAME = "name";
    const char* TMX_ATT_COLLIDER = "colider";

private:
    TTilemap m_Tilemap;
    StelPointI m_MapSize = StelPointI::Zero();
    size_t m_TilesetId = 0;
    TTileset m_Tileset;
    TCollider m_Colliders;

    void DrawLayer(TLayer layer, bool isCollider);

    //Parse the bloc of text to an TLayer. If error: Return TLayer empty.
    TLayer ParseDataToLayer(std::string data);
};