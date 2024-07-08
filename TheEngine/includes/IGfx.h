#pragma once
#include <string>
#include "StelColor.h"

/// <summary>
/// �Flip� est une classe servant � regrouper les combinaisons de flip possible pour une texture
/// </summary>
struct StelFlip
{
	bool h;
	bool v;
};

struct StelPointI
{
	int x;
	int y;
};

struct StelPointF
{
	float x;
	float y;
};

struct StelRectI 
{
	int x;
	int y;
	int w;
	int h;
};

struct StelRectF
{
	float x;
	float y;
	float w;
	float h;
};

class IGfx 
{
public:
	//static const char* ASSETS_FONTS_DIR;
	virtual ~IGfx() = default;
	virtual bool Initialize(const std::string& title, int w, int h, const char* msgError) = 0;
	virtual void Shutdown() = 0;
	virtual void SetColor(const StelColor& color) = 0;
	virtual void Clear() = 0;
	virtual void Present() = 0;
	virtual void DrawRect(float x, float y, float w, float h, const StelColor& color) = 0;
	virtual void DrawRect(const StelRectF& rect, const StelColor& color) = 0;
	virtual void FillRect(float x, float y, float w, float h, const StelColor& color) = 0;
	virtual void FillRect(const StelRectF& rect, const StelColor& color) = 0;
	virtual void DrawLine(StelPointF posStart, StelPointF posEnd, const StelColor& color) = 0;
	virtual void DrawCircle(StelPointF point, float r, const StelColor& color) = 0;
	virtual void DrawPoint(StelPointF point, const StelColor& color) = 0;
	virtual size_t LoadTexture(const std::string& filename) = 0;
	virtual void DrawTexture(size_t id, const StelRectI& src, const StelRectF& dst,
		double angle, const StelRectF& pivot, const StelFlip& flip, const StelColor& color) = 0;
	virtual void DrawTexture(size_t id, const StelRectF& dst, const StelColor& color) = 0;
	virtual void DrawTexture(size_t id, const StelColor& color) = 0;
	virtual void GetTextureSize(size_t id, int* w, int* h) = 0;
	virtual size_t LoadFont(const std::string& filename, int fontSize) = 0;
	virtual void DrawString(const std::string& text, size_t fontId, const StelPointF& position, const StelColor& color) = 0;
	virtual void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) = 0;
};
