#pragma once

#include <iostream>
#include <list>
#include <functional>

#include <SDL.h>

#include <glad.h>
#include "..\utils\common.h"


namespace cyx {



	class Window {
	
	public:
		using Event = SDL_Event;
		using Key = u8; 
		using EventCallback = void (*)(Event&);
		
		Window(const char* title, int width = 640, int height = 640);
		~Window();

		auto on_update() -> void;
		auto on_event(SDL_Event& e)  -> void;

		auto clear();

		auto width()->u32;
		auto height()->u32;
		auto keys() -> const u8*;
		auto add_callback(EventCallback fn) -> void;
		auto remove_callback(EventCallback fn) -> void;

		auto set_width(u32 new_width) -> void;
		auto set_height(u32 new_height) -> void;

		auto set_fullscreen(bool fullscreen) -> void;
		auto set_title(const char* title) -> void;
		
		auto swap_buffer() -> void;

		auto window_handle() ->	SDL_Window*;
		auto context_handle()->	SDL_GLContext*;
		auto poll_events() -> void;

	private:
		SDL_Window* _window;
		SDL_GLContext _glcontext;
		const char* _title;
		u32 _width, _height;

		std::list<EventCallback> _event_callbacks;
		const u8* _keys;
	};
}