#include "SdlGfx.h"
#include "SDL.h"

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

	for (auto font : m_Fonts) 
	{
		if (font != nullptr)
		{
			delete font;
			font = nullptr;
		}
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

	m_Fonts = std::vector<TTF_Font*>();

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
}

void SdlGfx::DrawRect(const StelRectF& rect, const StelColor& color)
{
}

void SdlGfx::FillRect(float x, float y, float w, float h, const StelColor& color)
{
}

void SdlGfx::FillRect(const StelRectF& _rect, const StelColor& color)
{
	SetColor(color);
	SDL_Rect sdlRect{ _rect.x, _rect.y, _rect.w,  _rect.h };
	SDL_RenderFillRect(m_Renderer, &sdlRect);
}

void SdlGfx::DrawLine(StelPointF posStart, StelPointF posEnd, const StelColor& color)
{
}

size_t SdlGfx::LoadTexture(const std::string& filename)
{
	return size_t();
}

void SdlGfx::DrawTexture(size_t id, const StelRectI& src, const StelRectF& dst, double angle, const StelFlip& flip, const StelColor& color)
{
}

void SdlGfx::DrawTexture(size_t id, const StelColor& dst, const StelColor& color)
{
}

void SdlGfx::DrawTexture(size_t id, const StelColor& color)
{

}

void SdlGfx::GetTextureSize(size_t id, int* w, int* h)
{
}

size_t SdlGfx::LoadFont(const std::string& filename, int fontSize)
{
	size_t sizeFont = static_cast<size_t>(fontSize);
	TTF_Font* font = TTF_OpenFont(filename.c_str(), sizeFont);
	m_Fonts.push_back(font);
	return m_Fonts.size() - 1;
}

void SdlGfx::DrawString(const std::string& text, size_t fontId, float x, float y, const StelColor& color)
{
	TTF_Font* font = m_Fonts.at(fontId);

	// this is the color in rgb format,
	// maxing out all would give you the color white,
	// and it will be your text's color
	SDL_Color sdlColor = { color.red, color.green, color.blue };

	// as TTF_RenderText_Solid could only be used on
	// SDL_Surface then you have to create the surface first
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font, text.c_str(), sdlColor);

	// now you can convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(m_Renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = x;  //controls the rect's x coordinate 
	Message_rect.y = y; // controls the rect's y coordinte
	Message_rect.w = 100; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	SDL_RenderCopy(m_Renderer, Message, NULL, &Message_rect);
	
}

void SdlGfx::GetTextSize(const std::string& text, size_t fontId, int* w, int* h)
{
}
