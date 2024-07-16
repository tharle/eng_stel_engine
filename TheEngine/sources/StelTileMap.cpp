#include "StelTileMap.h"
#include <StelEngine.h>

StelTileMap::StelTileMap() : StelTileMap(nullptr)
{
}

StelTileMap::StelTileMap(StelEntity* parent) : StelComponent(parent)
{
}

void StelTileMap::Load(const std::string& filename, StelPointI mapSize, StelPointI tileSize, float scaleFactor)
{
    auto& graphics = Stel::Engine::Get().GetGfxService();
    m_TilesetId = graphics.LoadTexture(filename);
    m_TileSize = tileSize;
    m_MapSize = mapSize;
    m_ScaleFactor = scaleFactor;

    StelPointI textureSize = graphics.GetTextureSize(m_TilesetId);

    int _tilePerRow = textureSize.x / m_TileSize.x;
    int _tilePerCol = textureSize.y / m_TileSize.y;
    int _tileCount = _tilePerRow * _tilePerCol;

    for (int i = 0; i < _tileCount; i++)
    {
        int _ty = i / _tilePerRow;
        int _tx = i - _ty * _tilePerRow;

        StelRectI _tile = {
            _tx * m_TileSize.x,
            _ty * m_TileSize.y,
            m_TileSize.x,
            m_TileSize.y
        };

        m_Tileset.push_back(_tile);
    }
}

void StelTileMap::AddLayer(const std::string& layer, TLayer tiles, bool isCollider)
{
    if (isCollider) 
    {
        m_Colliders.push_back(tiles);
    }
    else if (m_Tilemap.count(layer) == 0)
    {
        m_Tilemap.emplace(layer, tiles);
    }
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

bool StelTileMap::IsColliding(const std::string& nameLayer, StelRectF rect, int* tileIndex)
{

    /*StelRectF _dst = {
                        static_cast<float>(x),
                        static_cast<float>(y),
                        static_cast<float>(m_TileSize.x),
                        static_cast<float>(m_TileSize.y)
    };

    _dst = _dst.Resize(m_ScaleFactor);
    _dst.x *= _dst.w;
    _dst.y *= _dst.h;*/

    /*auto tileSize =  m_TileSize.Resize(static_cast<int>(m_ScaleFactor));
    const int tLeftTile = Clamp(static_cast<int>(rect.x / tileSize.x), 0, m_MapSize.x * tileSize.x);
    const int tRightTile = Clamp(static_cast<int>((rect.x + rect.w) / tileSize.x), 0, m_MapSize.x * tileSize.x);
    const int tTopTile = Clamp(static_cast<int>(rect.y / tileSize.y), 0, m_MapSize.y * tileSize.y);
    const int tBottomTile = Clamp(static_cast<int>((rect.y + rect.h) / tileSize.y), 0, m_MapSize.y * tileSize.y);

    for (int i = tLeftTile; i <= tRightTile; i++)
    {
        for (int j = tTopTile; j <= tBottomTile; j++)
        {
            if (i < m_MapSize.x && j < m_MapSize.y)
            {
                if (m_Tilemap[layer][j][i] != 0)
                {
                    *tileIndex = m_Tilemap[layer][j][i];
                    Stel::Engine::Get().GetGfxService().DrawTexture(m_TilesetId, m_Tileset[*(tileIndex)], {});
                    return true;
                }
            }
        }
    }*/

    //TLayer layer = m_Tilemap[nameLayer];
    //StelPointF tailSize = m_TileSize.ToFloat();
    //for (float y = 0; y < layer.size(); y++)
    //{
    //    for (float x = 0; x < layer[y].size(); x++)
    //    {
    //        int _idx = layer[y][x];

    //        if (_idx >= 0)
    //        {
    //            //_idx -= 1;

    //            StelRectF dst = {
    //                x,
    //                y,
    //                tailSize.x,
    //                tailSize.y
    //            };

    //            dst = dst.Resize(m_ScaleFactor);
    //            dst.x *= dst.w;
    //            dst.y *= dst.h;

    //            Stel::Engine::Get().GetGfxService().DrawRect(dst, StelColor::GREEN);
    //        }
    //    }
    //}

    *tileIndex = -1;
    return false;
}
void StelTileMap::DrawLayer(TLayer layer, bool isCollider)
{
    
    StelPointF tailSize = m_TileSize.ToFloat();
    for (float y = 0; y < layer.size(); y++)
    {
        for (float x = 0; x < layer[y].size(); x++)
        {
            int _idx = layer[y][x];

            if (_idx >= 0)
            {
                //_idx -= 1;

                StelRectF dst = {
                    x,
                    y,
                    tailSize.x,
                    tailSize.y
                };

                dst = dst.Resize(m_ScaleFactor);
                dst.x *= dst.w;
                dst.y *= dst.h;

                if(isCollider) Stel::Engine::Get().GetGfxService().DrawRect(dst, StelColor::GREEN);
                else Stel::Engine::Get().GetGfxService().DrawTexture(m_TilesetId, m_Tileset[_idx], dst);
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