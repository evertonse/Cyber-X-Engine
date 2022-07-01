#include "Renderer.hpp"

namespace cyx {
	Renderer::Renderer(Window* window)
		:_context(window->renderer_handle())
	{

	}

	void Renderer::clear() {
		SDL_RenderClear(_context);
	}

	void Renderer::clear(u8 r, u8 g, u8 b, u8 a) {
		SDL_SetRenderDrawColor(_context, r, b, g, a);
		SDL_RenderClear(_context);
	}

	void Renderer::draw()
	{
		clear();
		persistent int r = 255, g = 255, b = 255, a = 1;
		r = (r + 1) % 255;
		g = (g + 1) % 125;
		b = (b + 1) % 233;

		SDL_Delay(4);

		present();
		// <End> draw call
	}

	void Renderer::draw_quad(u32 x, u32 y, u32 width, u32 height, u32 color)
	{
	}


	void Renderer::present() {
		SDL_RenderPresent(_context);
	}

}