#pragma once
#include <iostream>

namespace null {
	enum class e_widget_flags {
		none,
		visible = 1 << 0,
		ignore_auto_positioning = 1 << 1,
		draw_on_top_layer = 1 << 2
	}; enum_create_bit_operators(e_widget_flags, true);
	enum_create_cast_operator(e_widget_flags, -);

	enum class e_widget_callbacks {
		on_focused,
		on_lost_focus,

		on_mouse_move,
		on_mouse_enter,
		on_mouse_exit,
		on_mouse_key_down,
		on_mouse_key_up,
		
		on_draw
	};

	enum class e_widget_event {
		mouse_move,
		mouse_key_down,
		mouse_key_up
	};

	enum class e_widget_state {
		none,
		active = 1 << 0,
		hovered = 1 << 1,
		focused = 1 << 2
	}; enum_create_bit_operators(e_widget_state, true);
	enum_create_cast_operator(e_widget_state, -);

	namespace gui {
		class c_widget {
		public:
			static inline std::map<e_widget_state, c_widget*> widgets{ };

		public:
			e_widget_flags flags{ e_widget_flags::visible };
			e_widget_state state{ };

			std::string name{ };
			vec2_t pos{ }, size{ };

			vec2_t clicked_offset{ };

			array_callbacks_t<e_widget_callbacks> callbacks{ };

			struct node_t {
				c_widget* parent{ };
				std::vector<std::shared_ptr<c_widget>> childs{ };

				std::vector<c_widget*> parent_node();
				std::vector<c_widget*> child_node();
			} node{ };

		public:
			c_widget(std::string_view _name) : name(_name) { }

			virtual bool can_hovered() { return rect_t{ pos, pos + size }.contains(input::mouse.pos); }

			virtual void add_widget(c_widget* widget);

			virtual void draw();

		public: //events
			virtual void on_child_focused(c_widget* child) { }
			virtual void on_child_lost_focus(c_widget* child, c_widget* new_focused_widget) { }

			virtual void on_focused();
			virtual void on_lost_focus(c_widget* new_focused_widget);

			virtual void on_mouse_move();
			virtual void on_mouse_enter();
			virtual void on_mouse_exit();

			virtual void on_mouse_key_down();
			virtual void on_mouse_key_up();

			virtual bool event_control(e_widget_event event);
		};
	}
}