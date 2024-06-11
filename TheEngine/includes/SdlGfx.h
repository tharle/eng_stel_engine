#pragma once
#include "IGfx.h"
#include "SDL.h"

class SdlGfx : public IGfx
{
private:
	SDL_Renderer* m_Renderer;
	SDL_Window* m_Window;
public:
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
	size_t LoadTexture(const std::string& filename) override;
	void DrawTexture(size_t id, const StelRectI& src, const StelRectF& dst,
		double angle, const StelFlip& flip, const StelColor& color) override;
	void DrawTexture(size_t id, const StelColor& dst, const StelColor& color) override;
	void DrawTexture(size_t id, const StelColor& color) override;
	void GetTextureSize(size_t id, int* w, int* h) override;
	size_t LoadFont(const std::string& filename, int fontSize) override;
	void DrawString(const std::string& text, size_t fontId, float x,
		float y, const StelColor& color) override;
	void GetTextSize(const std::string& text, size_t fontId, int* w, int* h) override;
};

