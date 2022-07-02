#pragma once
#include <containers/container.h>

namespace null::gui {
	class c_window : public i_container {
	public:
		static inline std::vector<std::shared_ptr<c_window>> window_stack{ };

		static void add_window(c_window* container) {
			window_stack.push_back(std::shared_ptr<c_window>(container));
		}

	public:
		struct style_t {
			float titlebar_height{ 15 };
			float titlebar_text_offset{ 10 };
			color_t titlebar_color{ 100, 100, 255 };

			color_t background_color{ 30, 30, 30 };

			bool moving_only_titlebar{ true }; //if true, the window will only move past the titlebar

			vec2_t padding{ 10, 10 };

			float widget_padding{ 10.f };
		} style{ };

	public:
		c_window(std::string_view _name, vec2_t _pos, vec2_t _size) : i_container(_name) {
			pos = _pos; size = _size;
		}

		bool is_topmost() { return window_stack.back().get() == this; }
		
		void focus();

	public:
		void setup_auto_positioning() override;
		void append_auto_positioning(i_widget* widget) override;

		void setup() override;
		void draw() override;

	public: //events
		void on_child_focused(i_widget* child) override;
		void on_focused() override;
		void on_mouse_move() override;
		void on_mouse_key_down() override;
	};
}