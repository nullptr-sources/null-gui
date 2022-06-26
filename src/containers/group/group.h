#pragma once
#include <containers/container.h>

namespace null::gui {
	class c_group : public c_container {
	public:
		struct style_t {
			float titlebar_height{ 15 };
			float titlebar_text_offset{ 10 };
			color_t titlebar_color{ 100, 100, 255 };

			color_t background_color{ 40, 40, 40 };

			bool moving_only_titlebar{ true }; //if true, the window will only move past the titlebar

			vec2_t padding{ 10, 10 };

			float widget_padding{ 10.f };
		} style{ };

	public:

	public:
		c_group(std::string_view _name, vec2_t _size) : c_container(_name) {
			size = _size;
			working_region = { vec2_t{ 0, style.titlebar_height } + style.padding, size - style.padding };
		}

	public:
		void append_auto_positioning(c_widget* widget) override;

		void draw() override;
	};
}