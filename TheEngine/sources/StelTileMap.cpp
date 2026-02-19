#include "StelTileMap.h"
#include <StelEngine.h>
#include <regex>

StelTileMap::StelTileMap() : StelTileMap(nullptr)
{
}

StelTileMap::StelTileMap(StelEntity* parent) : StelComponent(parent)
{
}

void StelTileMap::Load(const std::string& filename)
{
    Load(filename, StelPointI::Zero());
}

void StelTileMap::Load(const std::string& filename, StelPointI mapSize)
{
    auto& graphics = Stel::Engine::Get().GetGfxService();
    m_TilesetId = graphics.LoadTexture(filename);
    m_MapSize = mapSize;

    StelPointI textureSize = graphics.GetTextureSize(m_TilesetId);

    StelRectI size = GetTransform().GetRect().ToInt();

    int _tilePerRow = textureSize.x / size.w;
    int _tilePerCol = textureSize.y / size.h;
    int _tileCount = _tilePerRow * _tilePerCol;

    for (int i = 0; i < _tileCount; i++)
    {
        int _ty = i / _tilePerRow;
        int _tx = i - _ty * _tilePerRow;

        StelRectI _tile = {
            _tx * size.w,
            _ty * size.h,
            size.w,
            size.h
        };

        m_Tileset.push_back(_tile);
    }
}

void StelTileMap::AddLayer(const std::string& layer, TLayer tiles, bool isCollider)
{
    // TODO: Add check "Name exist"
    if (isCollider) 
    {
        m_Colliders.push_back(tiles);
    }
    else if (m_Tilemap.count(layer) == 0)
    {
        m_Tilemap.emplace(layer, tiles);
    }
}

tinyxml2::XMLError StelTileMap::AddTmx(const std::string& name)
{
    // Read TMX file
    tinyxml2::XMLDocument tmxDoc;
    XMLCheckResult(tmxDoc.LoadFile(name.c_str()));

    tinyxml2::XMLElement* pMap = tmxDoc.FirstChildElement(TMX_TAG_MAP.c_str());
    
    // Check if there a root element in XML
    if (pMap == nullptr) return tinyxml2::XML_ERROR_PARSING_ELEMENT;

    // Read map size
    pMap->QueryIntAttribute(TMX_ATT_WIDTH.c_str(), &m_MapSize.x);
    pMap->QueryIntAttribute(TMX_ATT_HEIGHT.c_str(), &m_MapSize.y);
    printf("LOAD MAP SIZE: %i x %i\n", m_MapSize.x, m_MapSize.y);

    // Find all layers with names
    tinyxml2::XMLElement* cLayer = pMap->FirstChildElement(TMX_TAG_LAYER.c_str());
    while (cLayer != nullptr) {
        // Name
        const char* name;
        cLayer->QueryStringAttribute(TMX_ATT_NAME.c_str(), &name);
        bool isCollider = std::strcmp(name, TMX_ATT_COLLIDER) == 0;

        // Data
        tinyxml2::XMLElement* cData = cLayer->FirstChildElement(TMX_TAG_DATA.c_str());

        //Convert to layer
        std::string data = cData->GetText();
        TLayer layer = ParseDataToLayer(data);
        ParseLayerCheck(layer); // Check if is a valid layer

        // Add to layers
        AddLayer(name, layer, isCollider);

        // Move to the next sibling element with the same name
        cLayer = cLayer->NextSiblingElement(TMX_TAG_LAYER.c_str());
    }

    // Find first collider layer
    // convert to tiles and add to m_Colliders
    return tinyxml2::XML_SUCCESS;
}

TLayer StelTileMap::ParseDataToLayer(std::string data)
{
    TLayer layer = TLayer();
    //For each and convert all string to TLayer
    try {
        printf("data:\n%s\n", data.c_str());
        //Find all data and convert to a array string
        const std::regex regexFindDigit(R"(\d+)");
            std::vector<std::string> matches{
            std::sregex_token_iterator(data.begin(), data.end(), regexFindDigit),
            std::sregex_token_iterator() // End-of-sequence iterator
        };
        printf("RESULT:\n\n");
        int i = 0;
        int j = 0;
        std::vector<int> layerLine = std::vector<int>();
        for (const std::string& match : matches) {
            printf("%s.", match.c_str());
            
            // In TMX not set a tile is awayls 0 and
            // to Fix, we reduce by 1 all id tile.
            int value = std::stoi(match) - 1;

            // Convert to int and add to line
            layerLine.push_back(value);

            // Set for map size
            i = (i + 1) % m_MapSize.x;

            if (i == 0) {// Check if we are in a new line
                layer.push_back(layerLine);// Add line to TLayer
                layerLine = std::vector<int>(); //new line to Layer
                
                j++;
                if (j >= m_MapSize.y) break; // if the map is full, break it
                printf("\n");
            }
        }
        printf("\n------------------------------------------------------\n");

        // if sucess, return result Layer
        return layer;
    }
    catch (std::invalid_argument ex) {
        printf("StelTileMap->ParseDataToLaye error: %s\n", ex.what());
    }
    catch (std::out_of_range ex) {
        printf("StelTileMap->ParseDataToLayer error: %s\n", ex.what());
    }
    catch (...) {
        printf("StelTileMap->ParseDataToLayer error: Unknown exception caught\n");
    }

    // if any problem, return empty layer
    return TLayer();
}

TLayer StelTileMap::GetLayer(const std::string& name)
{
    if (m_Tilemap.count(name) > 0)
    {
        return m_Tilemap[name];
    }

    return TLayer{};
}

int Clamp(int value, const int min, const int max)
{
    if (value < min)
    {
        value = min;
    }
    else if (value > max)
    {
        value = max;
    }

    return value;
}

bool StelTileMap::IsColliding(StelRectF boxCollider, int* tileIndex)
{
    auto tileSize = GetTransform().GetTrueRect();
    const int tLeftTile = Clamp(static_cast<int>(boxCollider.x / tileSize.w), 0, m_MapSize.x);
    const int tRightTile = Clamp(static_cast<int>(boxCollider.x / tileSize.w) + 1, 0, m_MapSize.x);
    const int tTopTile = Clamp(static_cast<int>(boxCollider.y / tileSize.h), 0, m_MapSize.y);
    const int tBottomTile = Clamp(static_cast<int>(boxCollider.y / tileSize.h) + 1, 0, m_MapSize.y);

    for (int x = tLeftTile; x <= tRightTile; x++)
    {
        for (int y = tTopTile; y <= tBottomTile; y++)
        {
            StelRectF tileRect = { 
                (static_cast<float>(x) * tileSize.w), 
                (static_cast<float>(y) * tileSize.h),
                tileSize.w,  
                tileSize.h 
            };

            if (!Stel::Engine::Get().GetPhysic().CheckRects(boxCollider, tileRect)) continue;

            for (auto layerCollider : m_Colliders) 
            {
                if (layerCollider[y][x] >= 0)
                {
                    return true;
                }
            }
        }
    }

    *tileIndex = -1;
    return false;
}
void StelTileMap::DrawLayer(TLayer layer, bool isCollider)
{
    
    StelPointF tailSize = GetTransform().Size;
    for (int y = 0; y < layer.size(); y++)
    {
        for (int x = 0; x < layer[y].size(); x++)
        {
            int _idx = layer[y][x];
            if (_idx == -1) continue;

            StelFlip flip = {false, false};
            if (_idx < -1) 
            {
                _idx = (_idx + 1) * -1;
                flip.h = true;
            }

            if (_idx >= 0)
            {
                //_idx -= 1;

                StelRectF dst = {
                    static_cast<float>(x),
                    static_cast<float>(y),
                    tailSize.x,
                    tailSize.y
                };

                dst = dst.Resize(GetTransform().Scale);
                dst.x *= dst.w;
                dst.y *= dst.h;

                if(isCollider) Stel::Engine::Get().GetGfxService().DrawRect(dst, StelColor::GREEN);
                else Stel::Engine::Get().GetGfxService().DrawTexture(m_TilesetId, m_Tileset[_idx], dst, flip);
            }
        }
    }
}


void StelTileMap::Draw()
{
    TLayer layer = m_Tilemap["level_1_collider"];

    for (auto layer : m_Tilemap)
    {
        DrawLayer(layer.second, false);
    }
    
    if (!DrawColliders) return;

    for (auto layer : m_Colliders) 
    {
        DrawLayer(layer, true);
    }
}