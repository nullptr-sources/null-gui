#pragma once
#include <widgets/widget.h>
#include <type_traits>

namespace null::gui {
	class i_container : public i_widget {
	public:
		struct auto_positioning_t {
			vec2_t max_position{ };
			vec2_t next_position{ };
		} auto_positioning; //struct for auto positioning child widgets

	public:
		i_container(std::string_view _name) : i_widget(_name) { }

		virtual void open() { flags |= e_widget_flags::visible; }
		virtual void close() { flags &= ~e_widget_flags::visible; }

		virtual void setup_auto_positioning();
		virtual void append_auto_positioning(i_widget* widget);

		virtual void setup() override;
		virtual void draw() override;
	};
}