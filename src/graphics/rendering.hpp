#pragma once
#include "common.h"
#include "window.hpp"
#include "vertex.hpp"
#include "shader.hpp"
#include "texture.hpp"

#define glLogCall(x) glClearErrors();x;glPrintErrors(#x,__FILE__,__LINE__)

namespace cyx {
	class VertexArray; 
	class VertexIndex;
	class Shader;
	class Texture;

	static void 
	glClearErrors(){
		while(glGetError() != GL_NO_ERROR);
	}
	
	static void 
	glPrintErrors(const char* function_name, const char* file_name, int line){
		GLenum error;
		error = glGetError();
		while(error != GL_NO_ERROR) {
			std::cout << "[GL Error]" <<"errocode: 0x"<< std::hex << error 
				<< " at function: " << function_name 
				<< " on file: " << file_name 
				<< " on line: " << line 
				<< std::endl;  
			error = glGetError();
		}
	}
	
	class Renderer {
	public:
		Renderer();
		~Renderer();

		void clear(void);
		auto enable_blending() -> void;
		void clear(u8 r, u8 g, u8 b, u8 a);
		void set_clear_color(u8 r, u8 g, u8 b, u8 a);
		auto set_viewport(u32 x, u32 y, u32 width, u32 height)  -> void;
		

		void draw_quad(u32 x, u32 y, u32 width, u32 height, u32 color = 0xFF'FF'FF'FF);
		
		
		auto present() -> void;
		auto draw(const VertexArray& va, const VertexIndex& vi, const Shader& shader) -> void;
		auto draw(const VertexArray& va, const VertexIndex& vi, const Shader& shader, const Texture& tex) -> void;
		

	private:
		union {
			u32 _color;
			u8 r,g,b,a;
		};
	};


}
