#pragma once
/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include "common.h"
#include "nuklear_settings.h"
#include "nuklear.h"
#include "nuklear_sdl_gl3.h"

#define MAX_VERTEX_MEMORY 512 * 1024
#define MAX_ELEMENT_MEMORY 128 * 1024

/* ===============================================================
 *
 *                          EXAMPLE
 *
 * ===============================================================*/
/* This are some code examples to provide a small overview of what can be
 * done with this library. To try out an example uncomment the defines */
/*#define INCLUDE_ALL */
#define INCLUDE_STYLE
#define INCLUDE_CALCULATOR 
/*#define INCLUDE_CANVAS */
//#define INCLUDE_OVERVIEW
/*#define INCLUDE_NODE_EDITOR */

#ifdef INCLUDE_ALL
  #define INCLUDE_STYLE
  #define INCLUDE_CALCULATOR
  #define INCLUDE_CANVAS
  #define INCLUDE_OVERVIEW
  #define INCLUDE_NODE_EDITOR
#endif

#ifdef INCLUDE_STYLE
  #include "style.c"
#endif
#ifdef INCLUDE_CALCULATOR
  #include "calculator.c"
#endif
#ifdef INCLUDE_CANVAS
  #include "canvas.c"
#endif
#ifdef INCLUDE_OVERVIEW
  #include "overview.c"
#endif
#ifdef INCLUDE_NODE_EDITOR
  #include "node_editor.c"
#endif

namespace cyx {
	class GUI {
	public:
		
		GUI(SDL_Window* win);
		auto on_update() 	-> void;
		auto render() -> void;
		auto on_create() -> void;
		auto on_destroy() -> void;
		
		auto begin_event() -> void;
		static auto on_event(SDL_Event& e)-> void;
		auto end_event() -> void;

		auto color_picker() -> u32; 

		auto slider(float max) -> float;

		static auto cleanup() -> int;
	
	public:
		SDL_Window *win;
		struct nk_context *ctx;
		struct nk_colorf bg;
	};
}
