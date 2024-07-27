#include "StelTileMap.h"
#include <StelEngine.h>

StelTileMap::StelTileMap() : StelTileMap(nullptr)
{
}

StelTileMap::StelTileMap(StelEntity* parent) : StelComponent(parent)
{
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
    for (float y = 0; y < layer.size(); y++)
    {
        for (float x = 0; x < layer[y].size(); x++)
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
                    x,
                    y,
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