#include <null-gui.h>
#include <containers/group/group.h>

namespace null::gui {
	void c_group::setup_auto_positioning() {
		i_container::setup_auto_positioning();
		auto_positioning.next_position += working_region.min;
	}

	void c_group::append_auto_positioning(i_widget* widget) {
		i_container::append_auto_positioning(widget);
		auto_positioning.next_position.y += style.widget_padding;
	}

	void c_group::setup() {
		working_region = { vec2_t{ 0, style.titlebar_height } + style.padding, size - style.padding };
		i_container::setup();
	}

	void c_group::draw() {
		gui_layer.draw_rect_filled(pos, pos + size, style.background_color); //draw background
		gui_layer.draw_rect_filled(pos, pos + vec2_t{ size.x, style.titlebar_height }, style.titlebar_color); //draw titlebar
		gui_layer.draw_text(name, rect_t{ pos, pos + vec2_t{ style.titlebar_text_offset, style.titlebar_height } }.center(), { }, e_text_flags::aligin_center_y); //draw titlebar text

		i_container::draw();
	}
}