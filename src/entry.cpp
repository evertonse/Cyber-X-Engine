#include "cyx.hpp"
#include <iostream>
#include <array>
#include <cmath>

//#define SDL_MAIN_HANDLED

class MyApp : public cyx::App {
	f32 scale = 1.0f;
	f32 translatex = 0.0f;
	f32 translatey = 0.0f;

public:

	cyx::Shader shader;
	MyApp():shader("assets\\shaders\\default.glsl") {}

	/*================================= PROGAM =====================================*/
	void on_create()  override {
		std::cout << "created program" << "\n";
		std::array<std::string, 3> a1{ "a", "b", "c" };
		shader.compile();


		shader.bind();

		
	}

	void on_update(f64 dt) override  {
		
		persistent f32 arr[4] = { 0.2f, 0.3f,0.8f, 1.0f };
		persistent f32 change = 0.01f;
		std::cout << arr[0] << "\n";
		arr[0] += change;
		if (arr[0] < 0.0f)
				change = 0.01f;
		else if (arr[0] > 1.0f)
				change = -0.01f;
		shader.uniform_float4("u_color", arr);

		glViewport(0, 0, screen_width(), screen_height());
		glClearColor(0.1f, 0.0f, 0.2f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		std::cout << "delta time: " << dt << "\n";

		using VBO = GLuint;
		using VAO = GLuint;
		persistent auto angle = 1.0f;
		angle += .002f;
		
		// positions
		f32 x1 = -0.3f*scale + translatex,   y1 = -0.3f*scale + translatey;
		f32 x2 =  0.3f*scale + translatex,   y2 = -0.3f*scale + translatey;
		f32 x3 = -0.0f*scale + translatex,   y3 =  0.3f*scale + translatey;
		
		// colors
		persistent f32 color1 = static_cast<f32>( (rand() % 255)) / 255.0f;
		persistent f32 color2 = static_cast<f32>( (rand() % 255)) / 255.0f;
		persistent f32 color3 = static_cast<f32>( (rand() % 255)) / 255.0f;
		
		color1 = (int(color1 + sin(rand())) % 255) / 255.0f;
		color2 = (int(color3 + sin(rand())) % 255) / 255.0f;
		color3 = (int(color2 + sin(rand())) % 255) / 255.0f;

		std::vector<f32> vertices = {
			// x                                 y                               z (color)
				x1*cos(angle) - y1*sin(angle) ,x1*sin(angle) + y1*cos(angle), color1,
				x2*cos(angle) - y2*sin(angle) ,x2*sin(angle) + y2*cos(angle), color2,
				x3*cos(angle) - y3*sin(angle) ,x3*sin(angle) + y3*cos(angle), color3,
		};

		VAO triangleVAO;
		// Generate Id for our VAO on gpu
		glGenVertexArrays(1, &triangleVAO);
		// select this one
		glBindVertexArray(triangleVAO);

		VBO triangleVBO;
		// Generate Id for our VBO on gpu
		glGenBuffers(1, &triangleVBO);
		glBindBuffer(GL_ARRAY_BUFFER,triangleVBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(f32), vertices.data(), GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
					0        /* from the index 0                */, 
					3        /* 3 floats                        */,
					GL_FLOAT /* Type of each data               */,
					GL_FALSE /* Not normalized                  */,
					0        /* No other attrib, so no stride   */,
					NULL
		);

		glBindVertexArray(triangleVAO);
		glBindBuffer(GL_ARRAY_BUFFER,triangleVBO);
		glDrawArrays(GL_TRIANGLES,0,3);
		// Undo everything done to cleanup the open gl context;
		glBindVertexArray(0);
		glDisableVertexAttribArray(0);

	}   
	auto on_event(Event& e ) -> void override { 
		auto&& buttons = this->keys();
		if (buttons[SDL_SCANCODE_W]) {
				translatey += 0.008f;
		}
		
		if (buttons[SDL_SCANCODE_S]) {
				translatey -= 0.008f;
		}

		if (buttons[SDL_SCANCODE_D]) {
				translatex += 0.008f;
		}

		if (buttons[SDL_SCANCODE_A]) {
				translatex -= 0.008f;
		}

		if (e.type == SDL_MOUSEWHEEL) {
				if (e.wheel.y > 0) {
					scale += 0.1f;
				}
				if (e.wheel.y < 0) {
					scale -= 0.1f;
				}

		}
	}
};

int main(int argc, char* argv[]) {
	MyApp a;
	a.start("cock");

	return 0;
}