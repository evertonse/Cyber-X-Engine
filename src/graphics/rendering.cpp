#include "rendering.hpp"

namespace cyx {
	// *------------------------------------------------------------------------------
	// | START Renderer
	// *------------------------------------------------------------------------------
	Renderer::Renderer() {
		set_clear_color(255, 255, 255, 255);
		enable_blending();


		i32 n_attr;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &n_attr);
		std::cout << "[Renderer]" << "Maximum nº of vertex attributes supported: " << n_attr << std::endl;
	}

	auto Renderer::enable_blending() -> void {
		glLogCall(
			glEnable(GL_BLEND)
		);
		std::cout << "[Renderer]" << "sucessfully enable blending\n";

		glLogCall(
			glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA)
		);
		std::cout << "[Renderer]" << "sucessfully set blending options\n";
	}

	Renderer::~Renderer() {

	}

	void Renderer::clear() {
		glLogCall(
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		);
	}

	void Renderer::clear(u8 r, u8 g, u8 b, u8 a) {
		set_clear_color(r, g, b, a);
		clear();
	}

	void Renderer::set_clear_color(u8 r, u8 g, u8 b, u8 a) {
		this->r = r; 
		this->b = b;
		this->g = g;
		this->b = b;
		this->a = a;
		glLogCall(
			glClearColor((f32)r / 255.0f, (f32)g / 255.0f, (f32)b / 255.0f, (f32)a / 255.0f)
		);
		std::cout << "[Renderer]" << "sucessfully set color to\n"
		<< " R: " << (u32) r
		<< " G: " << (u32) g
		<< " B: " << (u32) b
		<< " A: " << (u32) a
		<< std::endl;
	}
	
	auto Renderer::set_viewport(u32 x, u32 y, u32 width, u32 height) -> void {
		glViewport(x, y, width, height);
	}

	auto Renderer::draw(const VertexArray& va, const VertexIndex& vi, const Shader& shader) -> void {

		std::cout << "[Renderer]" << "sucessfully set blending options\n";
		std::cout << "[Renderer]" << "GOT HERE 2\n";
		va.bind();
		shader.bind();
		vi.bind();
		std::cout << "[Renderer]" << "GOT HERE 3\n";
		std::cout << "vi.count()" << vi.count();
		glLogCall(
			glDrawElements(GL_TRIANGLES, vi.count(), GL_UNSIGNED_INT, NULL);
		);
		std::cout << "[Renderer]" << "GOT HERE 4\n";
		// <End> draw call
	}

	auto Renderer::draw(const VertexArray& va, const VertexIndex& vi, const Shader& shader, const Texture& tex) -> void {

		std::cout << "[Renderer]" << "sucessfully set blending options\n";
		std::cout << "[Renderer]" << "GOT HERE 2\n";
		va.bind();
		shader.bind();
		vi.bind();
		tex.bind();
		std::cout << "[Renderer]" << "GOT HERE 3\n";
		std::cout << "vi.count()" << vi.count();
		glLogCall(
			glDrawElements(GL_TRIANGLES, vi.count(), GL_UNSIGNED_INT, NULL);
		);
		std::cout << "[Renderer]" << "GOT HERE 4\n";
		// <End> draw call
	}

	void Renderer::draw_quad(u32 x, u32 y, u32 width, u32 height, u32 color)
	{
	}

	// x------------------------------------------------------------------------------
	// | END Renderer
	// x------------------------------------------------------------------------------
		
}