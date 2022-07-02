#pragma once
#include <widgets/widget.h>
#include <type_traits>

namespace null {
	enum class e_container_flags {
		none,
		auto_size = 1 << 0
	}; enum_create_bit_operators(e_container_flags, true);
	enum_create_cast_operator(e_container_flags, -);

	namespace gui {
		class i_container : public i_widget {
		public:
			struct auto_positioning_t {
				vec2_t max_position{ };
				vec2_t next_position{ };
			} auto_positioning; //struct for auto positioning child widgets

			e_container_flags container_flags{ };
		public:
			i_container(std::string_view _name) : i_widget(_name) { }

			virtual void open() { flags |= e_widget_flags::visible; }
			virtual void close() { flags &= ~e_widget_flags::visible; }

			virtual void append_auto_size();
			virtual void setup_auto_positioning();
			virtual void append_auto_positioning(i_widget* widget);

			virtual void setup() override;
			virtual void draw() override;
		};
	}
}