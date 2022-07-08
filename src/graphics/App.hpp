#pragma once
#include "Window.hpp"
#include "../utils/common.h"

namespace cyx {

	class App
	{
	public:
		using Event = Window::Event;
		using Key = u8;
		friend int ::main(int argc, char** argv);

		struct Mouse {
			bool rclick, lclick;
			int x, y;
		};

		App(const char* name = "Cyber X App");
		virtual ~App();

		void start(const char* name="Cyber X App", u32 width=640, u32 height=480);

		virtual void on_create();
		virtual void on_update(f64 dt);
		virtual void on_event(Event& e);
		virtual void on_destroy();

		auto	screen_width()  -> u32;
		auto	screen_height() -> u32;

		const Key* keys();
		Mouse& mouse();

		auto window() -> Window& { return  _window; }

	private:
		Window _window;
		bool _running = true;
		bool _minimized = false;
		bool _fullscreen = false;

	
	// /* static */ public: 

	//	static App& instance();
	//
	/* static */ private: 
		static App* _instance;
		static void on_internal_update(Event& e);
	};

	App* App::_instance = nullptr;
}