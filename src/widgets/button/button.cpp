#include <null-gui.h>
#include <widgets/button/button.h>

namespace null::gui {
	void c_button::draw() {
		color_t button_color{ style.default_color };
		if(state & e_widget_state::active) button_color = style.active_color;
		else if(state & e_widget_state::hovered) button_color = style.hovered_color;

		gui_layer.draw_rect_filled(pos, pos + size, button_color);
		gui_layer.draw_text(name, rect_t{ pos, pos + size }.center(), style.text_color, e_text_flags::aligin_center);

		c_widget::draw();
	}
}