#pragma once
#include <containers/container.h>

namespace null::gui {
	class c_window : public c_container {
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
		c_window(std::string_view _name, vec2_t _pos, vec2_t _size) : c_container(_name) {
			pos = _pos; size = _size;
			working_region = { vec2_t{ 0, style.titlebar_height } + style.padding, size - style.padding };
		}

		void focus() { std::ranges::rotate(window_stack, std::next(std::ranges::find_if(window_stack, [=](const std::shared_ptr<c_window> winodw) { return winodw.get() == this; }))); }
		bool is_topmost() { return window_stack.back().get() == this; }

	public:
		void append_auto_positioning(c_widget* widget) override;

		void draw() override;

	public: //events
		void on_child_focused(c_widget* child) override;
		void on_focused() override;
		void on_mouse_move() override;
		void on_mouse_key_down() override;
	};
}