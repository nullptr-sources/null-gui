#include <null-gui.h>
#include <containers/window/window.h>

namespace null::gui {
	void c_window::append_auto_positioning(c_widget* widget) {
		c_container::append_auto_positioning(widget);
		auto_positioning.next_position.y += style.widget_padding;
	}

	void c_window::draw() {
		gui_layer.draw_rect_filled(pos, pos + size, style.background_color); //draw background
		gui_layer.draw_rect_filled(pos, pos + vec2_t{ size.x, style.titlebar_height }, style.titlebar_color); //draw titlebar
		gui_layer.draw_text(name, rect_t{ pos, pos + vec2_t{ style.titlebar_text_offset, style.titlebar_height } }.center(), { }, e_text_flags::aligin_center_y); //draw titlebar text

		auto_positioning.next_position = pos + working_region.min;

		c_container::draw();
	}

	void c_window::on_child_focused(c_widget* child) {
		c_container::on_child_focused(child);

		if(!is_topmost()) focus();
	}

	void c_window::on_focused() {
		c_container::on_focused();

		if(!is_topmost()) focus();
	}

	void c_window::on_mouse_move() {
		c_container::on_mouse_move();

		if(state & e_widget_state::active) {
			pos = input::mouse.pos - clicked_offset;
		}
	}

	void c_window::on_mouse_key_down() {
		c_container::on_mouse_key_down();

		clicked_offset = input::mouse.pos - pos;
	}
}