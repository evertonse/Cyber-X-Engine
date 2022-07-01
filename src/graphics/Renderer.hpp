#pragma once

#include "..\utils\common.h"
#include "Window.hpp"

namespace cyx {
	class Renderer {

	public:
		Renderer(Window *window);
		void clear(void);
		void clear(u8 r, u8 g, u8 b, u8 a);
		void draw();
		void draw_quad(u32 x, u32 y, u32 width, u32 height, u32 color = 0xFF'FF'FF'FF);
		void present();

	private:
		SDL_Renderer* _context;
	};

}