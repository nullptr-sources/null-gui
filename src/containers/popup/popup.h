#pragma once
#include <containers/container.h>

namespace null::gui {
	class c_popup : public i_container {
	public:
		struct style_t {
			color_t titlebar_color{ 255, 100, 100 };
			float titlebar_height{ 20.f };

			color_t background_color{ 10, 10, 10 };

			vec2_t padding{ 10, 10 };

			float widget_padding{ 10.f };
		} style{ };

	public:
		c_popup(std::string_view _name) : i_container(_name) {
			flags &= ~e_widget_flags::visible;
			working_region = { vec2_t{ 0, style.titlebar_height } + style.padding, size - style.padding };
		}

		bool can_close_on_lost_focus(i_widget* new_focused_widget);

	public:
		void open() override;
		void close() override;

		void setup_auto_positioning() override;
		void append_auto_positioning(i_widget* widget) override;
		void draw() override;

	public: //events
		void on_child_lost_focus(i_widget* child, i_widget* new_focused_widget) override;
		
		void on_focused() override;
		void on_lost_focus(i_widget* new_focused_widget) override;
	};
}