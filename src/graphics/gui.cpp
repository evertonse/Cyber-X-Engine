#include "nuklear_implementation.h"
#include "nuklear_settings.h"
#include "gui.hpp"


/* ===============================================================
 *
 *                          DEMO
 *
 * ===============================================================*/

auto cyx::GUI::cleanup() -> int {
	nk_sdl_shutdown();
	printf("[GUI] GOT HERE nk_sdl_shutdown\n");

	return 0;
}

namespace cyx {

	GUI::GUI(SDL_Window* win) {
		this->win = win;
	}

	auto GUI::on_destroy() -> void {
		cleanup();
	}



	auto GUI::on_update() -> void {
			
			/* GUI */
			if (nk_begin(ctx, "Hello", nk_rect(50, 50, 230, 250),
					NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
					NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
			{
					enum {EASY, HARD};
					static int op = EASY;
					static int property = 20;

					nk_layout_row_static(ctx, 30, 80, 1);
					if (nk_button_label(ctx, "button"))
							printf("button pressed!\n");


					nk_layout_row_dynamic(ctx, 30, 2);
					if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
					if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
					nk_layout_row_dynamic(ctx, 22, 1);
					nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);


					nk_layout_row_dynamic(ctx, 20, 1);
					nk_label(ctx, "background:", NK_TEXT_LEFT);
					nk_layout_row_dynamic(ctx, 25, 1);
					if (nk_combo_begin_color(ctx, nk_rgb_cf(bg), nk_vec2(nk_widget_width(ctx),400))) {
							nk_layout_row_dynamic(ctx, 120, 1);
							bg = nk_color_picker(ctx, bg, NK_RGBA);
							nk_layout_row_dynamic(ctx, 25, 1);
							bg.r = nk_propertyf(ctx, "#R:", 0, bg.r, 1.0f, 0.01f,0.005f);
							bg.g = nk_propertyf(ctx, "#G:", 0, bg.g, 1.0f, 0.01f,0.005f);
							bg.b = nk_propertyf(ctx, "#B:", 0, bg.b, 1.0f, 0.01f,0.005f);
							bg.a = nk_propertyf(ctx, "#A:", 0, bg.a, 1.0f, 0.01f,0.005f);
							nk_combo_end(ctx);
					}

			}
			nk_end	(ctx);

			/* -------------- EXAMPLES ---------------- */
			#ifdef INCLUDE_CALCULATOR
				calculator(ctx);
			#endif
			#ifdef INCLUDE_CANVAS
				canvas(ctx);	
			#endif
			#ifdef INCLUDE_OVERVIEW
				overview(ctx);
			#endif
			#ifdef INCLUDE_NODE_EDITOR
				node_editor(ctx);
			#endif

	}

	auto GUI::render() -> void {
	/* ----------------------------------------- */
	/* Draw */
	/* IMPORTANT: `nk_sdl_render` modifies some global OpenGL state
		* with blending, scissor, face culling, depth test and viewport and
		* defaults everything back into a default state.
		* Make sure to either a.) save and restore or b.) reset your own state after
		* rendering the UI. */
		nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_MEMORY, MAX_ELEMENT_MEMORY);
	}

	auto GUI::on_create() -> void {
		ctx = nk_sdl_init(win);
		/* Load Fonts: if none of these are loaded a default font will be used  */
		/* Load Cursor: if you uncomment cursor loading please hide the cursor */
		{
			struct nk_font_atlas *atlas;
			nk_sdl_font_stash_begin(&atlas);
			/*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
			/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);*/
			/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
			/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
			/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
			/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
			nk_sdl_font_stash_end();
			/*nk_style_load_all_cursors(ctx, atlas->cursors);*/
			/*nk_style_set_font(ctx, &roboto->handle);*/
		}
		/* style.c */
		#ifdef INCLUDE_STYLE
		/* ease regression testing during Nuklear release process; not needed for anything else */
		#ifdef STYLE_WHITE
		set_style(ctx, THEME_WHITE);
		#elif defined(STYLE_RED)
		set_style(ctx, THEME_RED);
		#elif defined(STYLE_BLUE)
		set_style(ctx, THEME_BLUE);
		#elif defined(STYLE_DARK)
		set_style(ctx, THEME_DARK);
		#endif
		#endif
	}

	auto GUI::begin_event() -> void {
		nk_input_begin(ctx);
	}
auto cyx::GUI::on_event(SDL_Event& e) -> void {

	if (e.type == SDL_QUIT) {
		printf("[GUI] GOT HERE SDL_QUIT\n");
		cleanup();
	}

	printf("[GUI] GOT HERE on_event");
	nk_sdl_handle_event(&e);
	printf("[GUI] GOT HERE, already nk_sdl_handled_event\n");
}

	auto GUI::end_event() -> void {	
		nk_input_end(ctx);
	}

	auto GUI::color_picker() -> struct nk_colorf {	
		static struct nk_colorf my_color = {0.8f, 0.3f, 0.2f, 1.0f};
		static const char my_text[] = "I'm the background color";
		auto&& flags = NK_WINDOW_TITLE | NK_WINDOW_MOVABLE ;
		nk_begin(ctx, "Color Picker", nk_rect(50,50, 255, 340),flags);
			nk_layout_row_dynamic(ctx, 200, 1);
			my_color = nk_color_picker(ctx, my_color, NK_RGBA);           /// Our color picker, returns the newly selected color which we can then use elsewhere
			nk_layout_row_dynamic(ctx, 20, 1);
			nk_text_colored(ctx, my_text, strlen(my_text), NK_TEXT_LEFT, nk_rgb_cf(my_color));   /// nk_text_colored takes an rgb color instead of rgba so we have to do some magic (nk_rgb_cf)
		nk_end(ctx);
		std::cout <<"[GUI] color: "
		  << " R: " << my_color.r 
			<< " G: " << my_color.g
		  << " B: " << my_color.b 
			<< " A: " << my_color.a;
		return my_color;
	}

}

