#pragma once
#include <widgets/widget.h>
#include <containers/popup/popup.h>

namespace null::gui {
	class c_button : public c_widget {
	public:
		struct style_t {
			color_t default_color{ 50, 50, 50 };
			color_t hovered_color{ 60, 60, 60 };
			color_t active_color{ 100, 100, 255 };

			color_t text_color{ 255, 255, 255 };
		} style;

	public:
		c_button(std::string_view _name) : c_widget(_name) { }

	public:
		void setup() override;
		void draw() override;
	};
}