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
    m_ScaleFactor = m_ScaleFactor;

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

void StelTileMap::AddLayer(const std::string& layer, TLayer tiles)
{
    if (m_Tilemap.count(layer) == 0)
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

bool StelTileMap::IsColliding(const std::string& layer, float x, float y, float w, float h, int* tileIndex)
{
    const int tLeftTile = Clamp(static_cast<int>(x / m_TileSize.x), 0, m_MapSize.x);
    const int tRightTile = Clamp(static_cast<int>((x + w) / m_TileSize.x), 0, m_MapSize.x);
    const int tTopTile = Clamp(static_cast<int>(y / m_TileSize.y), 0, m_MapSize.y);
    const int tBottomTile = Clamp(static_cast<int>((y + h) / m_TileSize.y), 0, m_MapSize.y);

    for (int i = tLeftTile; i <= tRightTile; i++)
    {
        for (int j = tTopTile; j <= tBottomTile; j++)
        {
            if (i < m_MapSize.x && j < m_MapSize.y)
            {
                if (m_Tilemap[layer][j][i] != 0)
                {
                    *tileIndex = m_Tilemap[layer][j][i];
                    return true;
                }
            }
        }
    }

    *tileIndex = -1;
    return false;
}

void StelTileMap::Draw()
{
    for (auto layer : m_Tilemap)
    {
        for (int y = 0; y < m_MapSize.y; y++)
        {
            for (int x = 0; x < m_MapSize.x; x++)
            {
                int _idx = layer.second[y][x];

                if (_idx > 0)
                {
                    _idx -= 1;
                    /*int _w = m_TileSize.x * m_ScaleFactor;
                    int _h = m_TileSize.y * m_ScaleFactor;
                    StelRectF _dst = {
                        static_cast<float>(x * _w),
                        static_cast<float>(y * _h),
                        static_cast<float>(_w),
                        static_cast<float>(_h)
                    };*/

                    StelRectF _dst = {
                        static_cast<float>(x),
                        static_cast<float>(y),
                        static_cast<float>(m_TileSize.x),
                        static_cast<float>(m_TileSize.y)
                    };

                    Stel::Engine::Get().GetGfxService().DrawTexture(m_TilesetId, m_Tileset[_idx], _dst.Resize(m_ScaleFactor));
                }
            }
        }
    }
}