#include "SdlGfx.h"
#include "SDL.h"
#include "SDL_image.h"
#include "StelEngine.h"

SdlGfx::~SdlGfx()
{
	if (m_Renderer != nullptr)
	{
		delete m_Renderer;
		m_Renderer = nullptr;
	}

	if (m_Window != nullptr)
	{
		delete m_Window;
		m_Window = nullptr;
	}

	if (m_TextureBuffer != nullptr) 
	{
		delete m_TextureBuffer;
		m_TextureBuffer = nullptr;
	}
}

bool SdlGfx::Initialize(const std::string& title, int w, int h, const char* msgError)
{
	if (SDL_Init(SDL_INIT_EVERYTHING != 0))
	{
		msgError = SDL_GetError();
		return false;
	}

	int _x = SDL_WINDOWPOS_CENTERED;
	int _y = SDL_WINDOWPOS_CENTERED;
	Uint32 _flag = SDL_WINDOW_TOOLTIP;
	m_Window = SDL_CreateWindow(title.c_str(), _x, _y, w, h, _flag);
	if (!m_Window)
	{
		msgError = SDL_GetError();
		return false;
	}

	_flag = SDL_RENDERER_ACCELERATED;
	m_Renderer = SDL_CreateRenderer(m_Window, -1, _flag);
	if (!m_Renderer)
	{
		msgError = SDL_GetError();
		return false;
	}

	TTF_Init();

	return true;
}

void SdlGfx::Shutdown()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	// TTF_CloseFont(font);
	SDL_Quit();
}

void SdlGfx::SetColor(const StelColor& color)
{
	SDL_SetRenderDrawColor(m_Renderer, color.red, color.green, color.blue, color.alpha);
}

void SdlGfx::Clear()
{
	SDL_RenderClear(m_Renderer);
}

void SdlGfx::Present()
{
	SDL_RenderPresent(m_Renderer);
}

void SdlGfx::DrawRect(float x, float y, float w, float h, const StelColor& color)
{
	SetColor(color);
	SDL_FRect sdlRect{ x, y, w, h };
	SDL_RenderDrawRectF(m_Renderer, &sdlRect);
}

void SdlGfx::DrawRect(const StelRectF& _rect, const StelColor& color)
{
	DrawRect(_rect.x, _rect.y, _rect.w, _rect.h, color);
}

void SdlGfx::FillRect(float x, float y, float w, float h, const StelColor& color)
{
	SetColor(color);
	SDL_FRect sdlRect{ x, y, w, h };
	SDL_RenderFillRectF(m_Renderer, &sdlRect);
}

void SdlGfx::FillRect(const StelRectF& _rect, const StelColor& color)
{
	FillRect(_rect.x, _rect.y, _rect.w, _rect.h, color);
}

void SdlGfx::DrawLine(StelPointF posStart, StelPointF posEnd, const StelColor& color)
{
	SetColor(color);
	SDL_RenderDrawLineF(m_Renderer, posStart.x, posStart.y, posEnd.x, posEnd.y);
}

void SdlGfx::DrawCircle(StelPointF point, float r, const StelColor& color)
{
    float tx = point.x;
    float ty = point.y;
    double angle = 0.0;

    while (angle < 6.3) // Code magic
    {
        tx = point.x + r * cos(angle);
        ty = point.y + r * sin(angle);
		DrawPoint({ tx, ty }, color);

        angle += 0.01;
    }
}

void SdlGfx::DrawPoint(StelPointF point, const StelColor& color)
{
	SetColor(color);
    SDL_RenderDrawPoint(m_Renderer, point.x, point.y);
}

size_t SdlGfx::LoadTexture(const std::string& filename, const char* msgError)
{
	const size_t _texId = std::hash<std::string>()(filename);

	if (m_TextureCache.count(_texId) > 0) return _texId;

	SDL_Texture* _texture = IMG_LoadTexture(m_Renderer, filename.c_str());
	if (_texture)
	{
		m_TextureCache.emplace(_texId, _texture);
		return _texId;
	}

	std::string msg = "Error with texture: " + filename;
	msgError = msg.c_str();

	return 0;
}

void SdlGfx::DrawTexture(size_t id, const StelRectI& src, const StelRectF& dst, double angle, const StelRectF& pivot,const StelFlip& flip, const StelColor& color)
{
	SDL_Rect _src = {src.x, src.y, src.w, src.h};
	SDL_FRect _dst = { dst.x, dst.y, dst.w, dst.h };
	SDL_FPoint _pivot = { pivot.x, pivot.y };

	int _flip = SDL_FLIP_NONE;
	if (flip.h)
	{
		_flip = SDL_FLIP_HORIZONTAL;
	}

	if (flip.v)
	{
		_flip |= SDL_FLIP_VERTICAL;
	}

	const SDL_RendererFlip _rf = static_cast<SDL_RendererFlip>(_flip);

	SetColorMode(id, color);
	
	SDL_RenderCopyExF(m_Renderer, m_TextureCache[id], &_src, &_dst, angle, &_pivot, _rf);
}

void SdlGfx::DrawTexture(size_t id, const StelRectF& dst, const StelColor& color)
{
	SDL_FRect _dst = { dst.x, dst.y, dst.w, dst.h };

	SetColorMode(id, color);

	SDL_RenderCopyF(m_Renderer, m_TextureCache[id], nullptr, &_dst);
}

void SdlGfx::DrawTexture(size_t id, const StelColor& color)
{
	SetColorMode(id, color);
	SDL_RenderCopy(m_Renderer, m_TextureCache[id], nullptr, nullptr);
}

void SdlGfx::GetTextureSize(size_t id, int* w, int* h)
{
	if (m_TextureCache.count(id) > 0)
	{
		SDL_QueryTexture(m_TextureCache[id], nullptr, nullptr, w, h);
	}
	else
	{
		*w = 0;
		*h = 0;
	}
}

size_t SdlGfx::LoadFont(const std::string& filename, size_t fontSize)
{
	const size_t _fntId = std::hash<std::string>()(filename) + fontSize;
	if (m_FontCache.count(_fntId) > 0)
	{
		return _fntId;
	}
	TTF_Font* _font = TTF_OpenFont(filename.c_str(), fontSize);
	if (_font)
	{
		m_FontCache.emplace(_fntId, _font);
		return _fntId;
	}
	std::string msg = "Error load the font: " + filename;
	Stel::Engine::Get().GetLoggerService().Print(LOG_ERROR, msg.c_str());

	return 0;
}

void SdlGfx::DrawString(const std::string& text, size_t fontId, const StelPointF& position, const StelColor& color)
{
	if (fontId == 0) return; // Font not loaded

	const SDL_Color _color = {
		static_cast<Uint8>(color.red),
		static_cast<Uint8>(color.green),
		static_cast<Uint8>(color.blue),
		static_cast<Uint8>(color.alpha)
	};

	SDL_Surface* _surface = TTF_RenderText_Solid(m_FontCache[fontId], text.c_str(), _color);

	SDL_FRect _dst = {
		position.x,
		position.y,
		_surface->w,
		_surface->h
	};

	SDL_Texture* textureBuffer = SDL_CreateTextureFromSurface(m_Renderer, _surface);
	SDL_RenderCopyF(m_Renderer, textureBuffer, nullptr, &_dst);
	SDL_FreeSurface(_surface);
	
}

void SdlGfx::GetTextSize(const std::string& text, size_t fontId, int* w, int* h)
{
	if (m_FontCache.count(fontId) > 0)
	{
		TTF_SizeText(m_FontCache[fontId], text.c_str(), w, h);
	}
	else
	{
		*w = 0;
		*h = 0;
	}
}

void SdlGfx::SetColorMode(size_t id, const StelColor& color)
{
    SDL_Texture* _tex = m_TextureCache[id];
    SDL_SetTextureBlendMode(_tex, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(_tex, color.alpha);
    SDL_SetTextureColorMod(_tex, color.red, color.green, color.blue);
}
