#include "Texture.h"
#include "Renderer.h"
#include "Core/Core.h"
#include <SDL2-devel-2.28.1-VC/SDL2-2.28.1/include/SDL_image.h>

namespace kiko
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}
	bool Texture::Load(const std::string& filename, Renderer& renderer)
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			// LOG_WARNING
			return false;
		}
		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			// LOG_WARNING
			return false;
		}
		return true;
	}
	vec2 Texture::GetSize()
	{
		ASSERT_LOG(m_texture, "texture cannot be null")
		SDL_Point point;
		// https://wiki.libsdl.org/SDL2/SDL_QueryTexture
		SDL_QueryTexture(m_texture, NULL, NULL, &point.x, &point.y );
		return vec2{ point.x, point.y };
	}
	bool Texture::Create(std::string filename, ...)
	{
		return false;
	}
}