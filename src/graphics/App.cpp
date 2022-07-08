#pragma once
#include "App.hpp"

namespace cyx {

	App::App(const char* name)
		:_window(Window{name})
	{
		App::_instance = this;
	}

	App::~App() {
		std::cout << "cyx::App is being called\n";
		// invalidating pointer
		App::_instance = nullptr;
	}

	void App::start(const char* title, u32 width, u32 height) {
		//_renderer.clear();
		//_renderer.present();

		_window.set_title (title);
		_window.set_width (width);
		_window.set_height(height);
		_window.add_callback(App::on_internal_update);
		
		this->on_create();
		
		f32 delta_time = 0.0;

		while (_running) {
			auto frame_start = static_cast<f64>(SDL_GetTicks());

			_window.on_update();
			this->on_update(delta_time);
			
			// already registered this->on_event to be called on event polled by this call below:
			_window.poll_events();

			 // double buffering
			_window.swap_buffer();

			auto frame_delay = static_cast<f64>(SDL_GetTicks()) - frame_start;

			delta_time = frame_delay;
			const auto FPS = 60.0;
			const auto FRAME_DELAY = 1000.0 / FPS;
			if (frame_delay < FRAME_DELAY)
			{
				// TODO: remove SDL injection on App class
				SDL_Delay(FRAME_DELAY - frame_delay);
			}

			std::cout << "FPS: " << 1000.0 / (static_cast<f64>(SDL_GetTicks()) - frame_delay) << "\n";
		}	
		this->on_destroy();
	}

	//App& App::instance()
	//{
	//	assert(_instance != nullptr && "App instance is invalid");
	//	return *App::_instance;
	//}


	void App::on_create() { return; }
	void App::on_update(f64 dt) { assert(0 && "client should implement on_update method"); }
	void App::on_event(Event& e) { return; }
	void App::on_destroy() { return; }

	auto App::screen_width() -> u32 {
		return _window.width();
	}

	auto App::screen_height() -> u32 {
		return _window.height();
	}

	const u8* App::keys()
	{
		return _window.keys();
	}

	// static:
	void App::on_internal_update(Event& e) {
		if (e.type == SDL_QUIT)
			_instance->_running = false;

		_instance->on_event(e);
	}
}