#pragma once
#include <containers/container.h>

namespace null::gui {
	class c_popup : public c_container {
	public:
		struct style_t {
			color_t titlebar_color{ 255, 100, 100 };
			float titlebar_height{ 20.f };

			color_t background_color{ 10, 10, 10 };
		} style{ };

	public:
		c_popup(std::string_view _name) : c_container(_name) { flags &= ~e_widget_flags::visible; }

		bool can_close_on_lost_focus(c_widget* new_focused_widget);

	public:
		void open() override;
		void close() override;

		void draw() override;

	public: //events
		void on_child_lost_focus(c_widget* child, c_widget* new_focused_widget) override;
		
		void on_focused() override;
		void on_lost_focus(c_widget* new_focused_widget) override;
	};
}