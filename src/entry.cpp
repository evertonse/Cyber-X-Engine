#pragma once
#include "cyx.hpp"
#include <iostream>
#include <array>
#include <cmath>
#include "Fastor.h"

//#define NUMCPP_NO_USE_BOOST  1 // we don't need to define this, because we already include this definition in the build. But intelisense is confused so....
#include "NumCpp.hpp"

//#undef NUMCPP_USE_MULTITHREAD // enables STL parallel execution policies throughout the library. Using multi-threaded algorithms can have negative performace impact for "small" array operations and should usually only be used when dealing with large array operations.
#include "nuklear_settings.h"

using namespace cyx;
using namespace Fastor;

struct color {
  union {
		struct {
	    u8 r,g,b,a;
		};
    u32 rgba;
  };
};

class MyApp : public App {
public:
//>> QUAD
	f32  angle = 0.02f;
	f32  translateby = 2.8f;
	f32  scaleby = 1.09f;
	nc::NdArray<f32> quad;
//<< QUAD

	f32 window_width  = (f32)1080;
	f32 window_height = (f32)720;
  
	color bg_color {0};

	Renderer renderer;
	VertexBuffer vb;
	VertexArray  va;
	VertexIndex  vi;

	VertexBufferLayout layout;

	std::array<f32,4> color;
/*
*/
	Shader shader;
	Texture texture;
	u32 texture_slot = 0;
	f32 slider_value = 0.0f;
	int index = 0;

	MyApp()
		: 
		shader("assets\\shaders\\default.glsl"),
		texture("assets\\textures\\instagram.png") 
		{}

	auto on_create() -> void override   {
		on_create_insta_logo();
	}

	auto on_update(f64 dt) -> void override {
		on_update_nukklear_integration(dt);
	}

	auto on_update_nukklear_integration(f64 dt) -> void   {
		u8 R = u8(bg_color.r),
			 G = u8(bg_color.g),
			 B = u8(bg_color.b),
			 A = u8(bg_color.a);
		int a = NULL;
		printf(
			"bd_color : %d:%d:%d:%d \n",
			bg_color.r,
			bg_color.g,
			bg_color.b,
			bg_color.a
		);
		printf(
			"multiplied color from printf%d:%d:%d:%d  \n"
			,R,G,B,A
		);
		
		std::cout << R<<':'<<G<<':'<<B<<':'<<A << std::endl;
		//renderer.set_clear_color(R,G,B,A ); // 
		
	
		bg_color.rgba = gui().color_picker();
		std::cout <<"bg_color.rgba "<< bg_color.rgba  << std::endl;
		slider_value = gui().slider(200.f);
		
		renderer.clear(R,G,B,A);
		
		translateby = slider_value;

		va.bind();
		vi.bind();
		vb.bind();

				
		std::vector<f32> model = {
			// x     y                            
			quad(0,0),  quad(0,1),  0.0f, 0.0f, // bottom left
			quad(1,0), 	quad(1,1),  0.0f, 1.0f,
			quad(2,0),  quad(2,1),  1.0f, 1.0f, // top right
			quad(3,0), 	quad(3,1),  1.0f, 0.0f  //
		};
		
		glLogCall(
			vb.bind();
		);

		glLogCall(
			vb.set_data(model.data(), model.size() * sizeof(f32))
		);

		texture.bind(texture_slot);
		shader.bind();
		
		// enabling what Nukklear has disableit
		//glLogCall(glEnablpe(GL_TEXTURE_2D));
		// enabling what Nukklear has disableit
		glLogCall(glEnable(GL_BLEND));
		// enabling what Nukklear has disableit
		glLogCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

		std::cout << "[Renderer]" << "sucessfully enable blending\n";

		window().set_height(window_height);
		window().set_width(window_width);

		renderer.set_viewport(0,0, screen_width(), screen_height());
		renderer.draw(va,vi,shader);

		va.unbind();
		vi.unbind();
		vb.unbind();
		texture.unbind();
		shader.unbind();


	//	nk_clear(_gui.ctx);
	//	nk_buffer_clear(&_gui.ctx->memory);

		/* setup global state */


	}
	
	auto on_destroy() -> void override {
		std::cout << "[MyApp] On Destroy" << "\n";
	}

	/*================================= PROGAM =====================================*/
	auto on_create_insta_logo() -> void  {
		shader.compile();
		shader.bind();
		texture.bind(texture_slot);
		va.bind();

		window().set_height(window_height);
		window().set_width(window_width);
		renderer.set_viewport(0,0, screen_width(), screen_height());

		auto&& proj = cyx::ortho(0.0f,window_width,0.0f, window_height,-1.0f,1.0f).transpose();
		
		auto&& v = nc::NdArray<f32>{
			window_height/2, 
			window_height/2, 
			0, 
			1
		}.transpose();
	
		std::cout << "[MyApp] created program" << "\n";
		std::cout << "[MyApp] v\n" << v << "\n";
		std::cout << "[MyApp] v.shape\n" << v.shape() << "\n";
		std::cout << "[MyApp] proj\n" << proj << "\n";
		std::cout << "[MyApp] proj.shape\n" << proj.shape() << "\n";
		std::cout << "[MyApp] proj @ v\n" << nc::matmul(proj,v) << "\n";

		i32 slot = texture.slot();
		
		std::cout << "[MyApp] slot from texture = " << slot << "\n";

		shader.uniform_int1("u_texture", slot);
		shader.uniform_mat4("u_MVP", proj.data());
		
		quad = nc::NdArray<f32>{
				{0.0f,0.0f},
				{window_height,0.0f},
				{window_height,window_height},
				{0.0f,window_height},
		};
		
		std::vector<f32> model_with_texture_data = {
			// x     y                            
			quad(0,0),  quad(0,1),  0.0f, 0.0f, // bottom left
			quad(1,0), 	quad(1,1),  0.0f, 1.0f,
			quad(2,0),  quad(2,1),  1.0f, 1.0f, // top right
			quad(3,0), 	quad(3,1),  1.0f, 0.0f  //
		};

		std::vector<f32> vertices_texture = {
			// x     y                            
			0.f ,    0.f,   0.0f, 0.0f, // bottom left
			(f32)texture.width(), 	 0.f,  0.0f, 1.0f,
			(f32)texture.width(),  (f32)texture.height(),  1.0f, 1.0f, // top right
			
			0.f  , 	(f32)texture.height(),  1.0f, 0.0f  //
		};

		std::vector<u32> indices = {
			0,1,2,
			2,3,0,
			//0,3,1
		};

		auto& model = model_with_texture_data;

		glLogCall(
			vb.bind();
		);
		glLogCall(
			vb.set_data(model.data(), model.size() * sizeof(f32));
		);

		glLogCall(
			vi.set_data(indices.data(), indices.size() * sizeof(u32));
		);
		vi.set_count(indices.size());
		vi.bind();
		

		layout.add({VertexBufferAttr::Float2,VertexBufferAttr::Float2});

		va.add(vb,layout);
		//vb.set_attr(0,2,sizeof(f32)*2,0);
		
		color = std::array<f32,4>{1.0f,0.0f,0.8f, 1.0f};

		// everything is remembered by the vao so we can safely unbind the below:
		va.bind();

	};


	auto on_update_insta_logo(f64 dt) -> void    {
	  va.bind();
		vb.bind();
		vi.bind();
		shader.bind();
		texture.bind();
		std::cout << "[MyApp] bound everything\n"  << "\n";
		//shader.uniform_float4("u_color", this->color.data());
		
		// if we're using index buffer need to be Draw Elements
		// because the inedx buffer is already bound we can pass null as the index buffer pointer
		renderer.draw(va,vi,shader, texture);

		va.unbind();
		vb.unbind();
		vi.unbind();
		shader.unbind();
		texture.unbind();
		std::cout << "[MyApp] unbound everything\n"  << "\n";
	}

	auto  test_on_update(f64 dt) -> void   {
		static f32 arr[4] = { 0.2f, 0.3f,0.8f, 1.0f };
		static f32 change = 0.01f;
		std::cout << arr[0] << "\n";
		arr[0] += change;
		if (arr[0] < 0.0f)
				change = 0.01f;
		else if (arr[0] > 1.0f)
				change = -0.01f;
		//shader.uniform_float4("u_color", arr);

		std::cout << "delta time: " << dt << "\n";

		static auto angle = 1.0f;
		angle += .002f;
		
		// positions
		f32 x1 = -0.3f*scaleby + translateby,   y1 = -0.3f*scaleby + translateby;
		f32 x2 =  0.3f*scaleby + translateby,   y2 = -0.3f*scaleby + translateby;
		f32 x3 = -0.0f*scaleby + translateby,   y3 =  0.3f*scaleby + translateby;
		
		// colors
		static f32 color1 = static_cast<f32>( (rand() % 255)) / 255.0f;
		static f32 color2 = static_cast<f32>( (rand() % 255)) / 255.0f;
		static f32 color3 = static_cast<f32>( (rand() % 255)) / 255.0f;
		
		color1 = (int(color1 + std::sin(rand())) % 255) / 255.0f;
		color2 = (int(color3 + std::sin(rand())) % 255) / 255.0f;
		color3 = (int(color2 + std::sin(rand())) % 255) / 255.0f;

		std::vector<f32> vertices = {
			// x                                 y                               z (color)
			x1*cos(angle) - y1*sin(angle) ,x1*sin(angle) + y1*cos(angle), color1,
			x2*cos(angle) - y2*sin(angle) ,x2*sin(angle) + y2*cos(angle), color2,
			x3*cos(angle) - y3*sin(angle) ,x3*sin(angle) + y3*cos(angle), color3,
		};
		

		

		//va.bind();	
		//vb.bind();
		

		glDrawArrays(GL_TRIANGLES, 0, 3);
		// Undo everything done to cleanup the open gl context;
		//va.unbind();

	}   
	
	auto on_event(Event& e ) -> void override { 
		auto&& rot = rotation2D(angle);

		auto&& buttons = this->keys();
		
		if (buttons[SDL_SCANCODE_Q]) {
			auto&& offset = quad.copy() / 2.0f;
			quad -=  offset;
			quad = nc::matmul(quad,rot);
			quad +=  offset;
					
		}
		
		if (buttons[SDL_SCANCODE_E]) {
			auto&& offset = quad.copy() / 2.0f;
			quad -=  offset;
			quad = nc::matmul(quad,rot.transpose());
			quad +=  offset;
		}

		if (buttons[SDL_SCANCODE_W]) {
			quad(0,1) += translateby;
			quad(1,1) += translateby;
			quad(2,1) += translateby;
			quad(3,1) += translateby;
		}
		
		if (buttons[SDL_SCANCODE_S]) {
			quad(0,1) -= translateby;
			quad(1,1) -= translateby;
			quad(2,1) -= translateby;
			quad(3,1) -= translateby;
		}

		if (buttons[SDL_SCANCODE_D]) {
			quad(0,0) += translateby;
			quad(1,0) += translateby;
			quad(2,0) += translateby;
			quad(3,0) += translateby;
		}

		if (buttons[SDL_SCANCODE_A]) {
			quad(0,0) -= translateby;
			quad(1,0) -= translateby;
			quad(2,0) -= translateby;
			quad(3,0) -= translateby;
		}
		
		if (buttons[SDL_SCANCODE_RETURN]) {
			std::cin.ignore();
		}

		if (e.type == SDL_MOUSEWHEEL) {
				if (e.wheel.y > 0) {
					auto&& scale = scale2D(scaleby);
					
					std::cout << "there we go we're about to scale\n quad before" <<quad ;
					quad = nc::matmul(quad,scale);
					std::cout << "quad after scale" <<quad ;
					
					//std::cin.ignore();
				}
				if (e.wheel.y < 0) {
					auto&& scale = scale2D(1.0f/scaleby);
					quad = nc::matmul(quad,scale);
					//std::cin.ignore();
				}
		}
	}
};

/*/////////////////////////////////////////////////////////////|
																															 |
	WARNING: 																										 |
	  remove define VISUAL_STUDIO_DEBUG bellow, if you're not me |
																															 |
*//////////////////////////////////////////////////////////////|
#define VISUAL_STUDIO_DEBUG
int main(int argc, char* argv[]) {
#ifdef VISUAL_STUDIO_DEBUG
	change_working_directory("D:\\code\\Cyber-X-Engine");
#endif
	//exit(1);
	MyApp a;
	a.start("Cyber X");
	return 0;
}
