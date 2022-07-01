#include "Texture.hpp"
namespace cyx {


	Texture::Texture(const char* bmp_image_path)
	{
		//bmp_surface = SDL_LoadBMP("./images/showcase.bmp");
		_surface = SDL_LoadBMP(bmp_image_path);
		if (_surface == NULL)
		{
			std::cout << SDL_GetError() << "\n";
			exit(1);
		}
	}
	void Texture::load(SDL_Renderer* renderer)
	{
		this->_texture = SDL_CreateTextureFromSurface(renderer, this->_surface);
	}

	Texture::operator SDL_Texture* ()
	{
		return this->_texture;
	}	
	
	Texture::~Texture()
	{
		SDL_FreeSurface(_surface);
		SDL_DestroyTexture(_texture);
	}
}