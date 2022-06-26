#include <null-gui.h>
#include <containers/popup/popup.h>

namespace null::gui {
	bool c_popup::can_close_on_lost_focus(c_widget* new_focused_widget) {
		if(new_focused_widget) {
			if(auto parent_node = new_focused_widget->node.parent_node();
				std::ranges::find(parent_node, this) != parent_node.end()) return false;
		}

		if(auto parent_node = node.parent_node();
			std::ranges::find_if(parent_node, [=](c_widget* widget) {
				if(dynamic_cast<c_container*>(widget) && !dynamic_cast<c_popup*>(widget))
					return false;

				return widget == new_focused_widget;
				}) != parent_node.end()) return false;

		return true;
	}

	void c_popup::open() {
		c_container::open();

		node.parent->flags |= e_widget_flags::draw_on_top_layer;
	}

	void c_popup::close() {
		c_container::close();

		node.parent->flags &= ~e_widget_flags::draw_on_top_layer;
	}

	void c_popup::draw() {
		gui_layer.draw_rect_filled(pos, pos + size, style.background_color);
		gui_layer.draw_rect_filled(pos, pos + vec2_t{ size.x, style.titlebar_height }, style.titlebar_color);
		gui_layer.draw_text(name, rect_t{ pos, pos + vec2_t{ size.x, style.titlebar_height } }.center(), { }, e_text_flags::aligin_center);
		
		auto_positioning.next_position = pos + working_region.min + vec2_t{ 20, 20 };
		c_container::draw();
	}

	void c_popup::on_child_lost_focus(c_widget* child, c_widget* new_focused_widget) {
		c_widget::on_child_lost_focus(child, new_focused_widget);
		
		if(new_focused_widget == this) return;
		if(can_close_on_lost_focus(new_focused_widget)) close();
	}

	void c_popup::on_focused() {
		for(c_widget* widget : node.child_node()) { //closing all child popups
			if(c_popup* popup = dynamic_cast<c_popup*>(widget))
				popup->close();
		}

		c_widget::on_focused();
	}

	void c_popup::on_lost_focus(c_widget* new_focused_widget) {
		c_widget::on_lost_focus(new_focused_widget);

		if(can_close_on_lost_focus(new_focused_widget)) close();
	}
}