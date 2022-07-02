#include <null-gui.h>
#include <containers/window/window.h>

namespace null::gui {
	void c_window::focus() {
		if(auto finded = std::ranges::find_if(window_stack, [=](const std::shared_ptr<c_window> winodw) { return winodw.get() == this; });
			finded != window_stack.end())
			std::rotate(finded, std::next(finded), window_stack.end());
	}

	void c_window::setup_auto_positioning() {
		i_container::setup_auto_positioning();
		auto_positioning.next_position += working_region.min;
	}

	void c_window::append_auto_positioning(i_widget* widget) {
		i_container::append_auto_positioning(widget);
		auto_positioning.next_position.y += style.widget_padding;
	}

	void c_window::setup() {
		working_region = { vec2_t{ 0, style.titlebar_height } + style.padding, size - style.padding };
		i_container::setup();
	}

	void c_window::draw() {
		gui_layer.draw_rect_filled(pos, pos + size, style.background_color); //draw background
		gui_layer.draw_rect_filled(pos, pos + vec2_t{ size.x, style.titlebar_height }, style.titlebar_color); //draw titlebar
		gui_layer.draw_text(name, rect_t{ pos, pos + vec2_t{ style.titlebar_text_offset, style.titlebar_height } }.center(), { }, e_text_flags::aligin_center_y); //draw titlebar text

		gui_layer.draw_rect_filled(pos + working_region.min, pos + working_region.max, { 100, 100, 100, 50 });

		i_container::draw();
	}

	void c_window::on_child_focused(i_widget* child) {
		i_container::on_child_focused(child);

		if(!is_topmost()) focus();
	}

	void c_window::on_focused() {
		i_container::on_focused();

		if(!is_topmost()) focus();
	}

	void c_window::on_mouse_move() {
		i_container::on_mouse_move();

		if(state & e_widget_state::active) {
			pos = input::mouse.pos - clicked_offset;
		}
	}

	void c_window::on_mouse_key_down() {
		i_container::on_mouse_key_down();

		clicked_offset = input::mouse.pos - pos;
	}
}