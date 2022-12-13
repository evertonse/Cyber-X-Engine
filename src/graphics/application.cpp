#include "application.hpp"

namespace cyx {
	App* App::_instance = nullptr;

	App::App(const char* name)
		:_window(Window{name}),_gui(GUI{_window.native()})
	{
		App::_instance = this;
	}

	App::~App() {
		std::cout << "[App] cyx::App is being called\n";
		// invalidating pointer
		App::_instance = nullptr;
	}

	void App::start(const char* title, u32 width, u32 height) {
		_window.set_title (title);
		_window.set_width (width);
		_window.set_height(height);
		_window.add_callback(App::on_internal_update);
		_window.add_callback(GUI::on_event);
		this->on_create();
		_gui.on_create();
		
		f32 delta_time = 0.0;

		while (_running) {
			auto frame_start = static_cast<f64>(SDL_GetTicks());
			// already registered this->on_event to be called on event polled by this call below:

		
			
			this->	on_update(delta_time);
			_window.on_update();
			_gui.		on_update();
			
			_gui.render();
			 
			_gui.begin_event();
			_window.poll_events();
			_gui.end_event();
			
			// double buffering
			_window.swap_buffer();
			

			auto frame_delay = static_cast<f32>(_window.ticks()) - frame_start;

			delta_time = frame_delay;
			const auto FPS = 60.0;
			const auto FRAME_DELAY = 1000.0 / FPS;
			if (frame_delay < FRAME_DELAY) {
				// TODO: remove SDL injection on App class
				_window.delay(FRAME_DELAY - frame_delay);
			}
			std::stringstream buffer;
			buffer << title <<" FPS: " << 1000.0 / (static_cast<f64>(_window.ticks()) - frame_delay) << "\n";
			_window.set_title(buffer.str().c_str());
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
		if (e.type == SDL_QUIT) {
			_instance->_running = false;
		}

		_instance->on_event(e);
	}

	auto App::gui()->GUI {
		return _gui;
	}
}