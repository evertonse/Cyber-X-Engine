#include "Window.hpp"

#define SDL_ASSERT(SDL_Func,msg)  if( SDL_Func < 0 ) { std::cout << msg << "[Error]: " << SDL_GetError() << '\n'; }
namespace cyx {


	Window::Window(const char* title, int width, int height)
		:_title("default_name")
	{
		std::cout << "[Window] constructor called" << '\n';
		this->_width = width;
		this->_height = height;
		char* argv = (char*)"";
		//SDL_main(1, &argv);
		u32 sdlflags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
		//SDL_Init(SDL_INIT_EVERYTHING);
		// We only want the video's subsystem part of SDL
		u32 sdlcode;
		sdlcode = SDL_Init(SDL_INIT_VIDEO);
		
		SDL_ASSERT(sdlcode, " SDL failed init");

		// set opengl as core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
		
		// set the version we want 3.3, so Major = 3 and Minor = 3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);

		// enable doublebuffer, means the window will update twice as often
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
		// 24 bits color
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

		// use VSync
		sdlcode = SDL_GL_SetSwapInterval(1);
		SDL_ASSERT(sdlcode, "SDL_GL_SetSwapInterval failed init");
			
		// AFTER we set attr for GL, THEN we create the window
		this->_window = SDL_CreateWindow(
			_title,
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			_width, _height,
			sdlflags
		);

		// set title
		SDL_SetWindowTitle(this->_window, _title);

		sdlcode = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");
		SDL_ASSERT(sdlcode, " SDL_SetHint failed init");
		SDL_ShowCursor(1);


		// We set a glcontext
		this->_glcontext = SDL_GL_CreateContext(_window);
		
		// Dynamic Load the OpenGL function pointers
		gladLoadGLLoader(SDL_GL_GetProcAddress);
		glViewport(0,0,width,height);
		auto&& renderer = glGetString(GL_RENDERER);
		auto&& version	= glGetString(GL_VERSION);
		std::cout	<< "[GL] renderer:" << renderer << "\n"
					<< "[GL] version:" << version << "\n"
					<< "[GL] clearing color" << "\n";

		glClearColor(1.0, 1.0, 0.0, 1.0);
	}

	Window::~Window()
	{
		SDL_GL_DeleteContext(_glcontext);
		std::cout << "[Window] GL_DeleteContext called" << '\n';

		SDL_DestroyWindow(this->_window);
		std::cout << "[Window] SDL destryed window called" << '\n';
		SDL_Quit();
	}
	 
	auto Window::on_update() ->void
	{
	}

	auto Window::set_fullscreen(bool fullscreen) -> void
	{
		if (fullscreen)
			SDL_SetWindowFullscreen(this->_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		else
			SDL_SetWindowFullscreen(this->_window, false);
	}

	auto Window::swap_buffer() -> void
	{
		SDL_GL_SwapWindow(_window);
	}

	auto Window::on_event(SDL_Event& e) -> void
	{
	}

	auto Window::clear() {
	}

	auto Window::width() -> u32 {
		i32 width, height;
		SDL_GetWindowSize(_window, &width, &height);
		assert(_width == width && "[ERROR] somehow the width insnt the same");
		return _width;
	}

	auto Window::height() -> u32 {
		i32 width, height;
		SDL_GetWindowSize(_window,&width,&height);
		assert(_height  == height && "[ERROR] somehow the height insnt the same");
		return _height;
	}

	auto Window::keys() -> const u8*
	{
		return SDL_GetKeyboardState(NULL);;
	}

	auto Window::add_callback(EventCallback fn) -> void {
		_event_callbacks.push_back(fn);
	}

	auto Window::remove_callback(EventCallback fn) -> void {
		_event_callbacks.remove(fn);
	}
	
	auto Window::set_width(u32 new_width) -> void {
		_width = new_width;
		SDL_SetWindowSize(_window, new_width, _height);
	}

	auto Window::set_height(u32 new_height) -> void {
		_height = new_height;
		SDL_SetWindowSize(_window, _width, new_height);
	}

	auto Window::window_handle() -> SDL_Window*
	{
		return _window;
	}

	auto Window::context_handle() -> SDL_GLContext* {
		return &_glcontext;
	}	
	
	auto Window::set_title(const char* title) -> void {
		_title = title;
		SDL_SetWindowTitle(_window, _title);
	}

	auto Window::poll_events() -> void {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			//_keys = SDL_GetKeyboardState(NULL);
			this->on_event(e);
			// client code (App derived)
			for (auto& fn : _event_callbacks) {
				fn(e);
			}
		}
	}
}