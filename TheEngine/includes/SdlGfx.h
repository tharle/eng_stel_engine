#pragma once
#include "IGfx.h"
#include "SDL.h"
#include <map>
#include "SDL_ttf.h"


class SdlGfx : public IGfx
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
	SDL_Texture* m_TextureBuffer;
	
	typedef std::map<size_t, SDL_Texture*> TTextureMap;
	typedef std::map<size_t, TTF_Font*> TFontMap;

	TTextureMap m_TextureCache;
	TFontMap m_FontCache;

	void SetColorMode(size_t id, const StelColor& color);
public:
	~SdlGfx();
	bool Initialize(const std::string& title, int w, int h, const char* msgError) override;
	void Shutdown() override;
	void SetColor(const StelColor& color) override;
	void Clear() override;
	void Present() override;
	void DrawRect(float x, float y, float w, float h, const StelColor& color) override;
	void DrawRect(const StelRectF& rect, const StelColor& color) override;
	void FillRect(float x, float y, float w, float h, const StelColor& color) override;
	void FillRect(const StelRectF& rect, const StelColor& color) override;
	void DrawLine(StelPointF posStart, StelPointF posEnd, const StelColor& color) override;
	void DrawCircle(StelPointF point, float r, const StelColor& color) override;
	void DrawPoint(StelPointF point, const StelColor& color) override;
	size_t LoadTexture(const std::string& filename, const char* msgError) override;
	void DrawTexture(size_t id, const StelRectI& src, const StelRectF& dst,
		double angle, const StelRectF& pivot, const StelFlip& flip, const StelColor& color) override;
	void DrawTexture(size_t id, const StelRectF& dst, const StelColor& color) override;
	void DrawTexture(size_t id, const StelColor& color) override;
	void GetTextureSize(size_t id, int* w, int* h) override;
	size_t LoadFont(const std::string& filename, int fontSize, const char* msgError) override;
	void DrawString(const std::string& text, size_t fontId, const StelPointF& position, const StelColor& color) override;
	void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) override;
};

