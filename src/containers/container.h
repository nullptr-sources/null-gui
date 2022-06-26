#pragma once
#include <widgets/widget.h>
#include <type_traits>

namespace null::gui {
	class c_container : public c_widget {
	public:
		rect_t working_region{ };

		struct auto_positioning_t {
			vec2_t next_position{ };
		} auto_positioning; //struct for auto positioning child widgets

	public:
		c_container(std::string_view _name) : c_widget(_name) { }

		virtual void open() { flags |= e_widget_flags::visible; }
		virtual void close() { flags &= ~e_widget_flags::visible; }

		virtual void append_auto_positioning(c_widget* widget);
		virtual void draw() override;
	};
}