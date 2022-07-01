#pragma once

#include "../cyx.hpp"
#include "SDL.h"
#include "../utils/common.h"

namespace cyx {

	class Texture
	{
	public:
		Texture(const char* path);
		~Texture() = default;

		void load(SDL_Renderer* renderer);
		
		operator SDL_Texture* ();

	private :
		SDL_Surface* _surface;
		SDL_Texture* _texture;
	};

}
