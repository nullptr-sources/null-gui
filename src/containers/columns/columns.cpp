#include <null-gui.h>
#include <containers/columns/columns.h>

//@todo: rewrite this trash
namespace null::gui {
	void c_columns::c_column::append_auto_positioning(i_widget* widget) {
		i_container::append_auto_positioning(widget);
		size.y = auto_positioning.max_position.y - pos.y;
		auto_positioning.next_position.y += style.widget_padding;
	}

	bool c_columns::c_column::event_control(e_widget_event event) {
		for(std::shared_ptr<i_widget> child_widget : node.childs | std::views::reverse) {
			if(child_widget->flags & e_widget_flags::visible && child_widget->event_control(event)) return true;
		}
		return false;
	}

	void c_columns::append_auto_positioning(i_widget* widget) {
		widget->pos = auto_positioning.next_position;
		auto_positioning.next_position.x += widget->size.x + style.column_padding;
		auto_positioning.max_position = math::max(auto_positioning.max_position, widget->pos + widget->size);
	}

	void c_columns::setup() {
		setup_auto_positioning();
		for(auto& column : node.childs) {
			if(column->size.x == 0.f)
				column->size.x = (node.parent->working_region.size().x - (style.column_padding * (node.childs.size() - 1))) / node.childs.size();

			column->pos = auto_positioning.next_position;
			column->setup();
			append_auto_positioning(column.get());
		}

		size.y = auto_positioning.max_position.y - pos.y;
	}

	void c_columns::draw() {
		for(auto& column : node.childs) {
			column->draw();
		}

		gui_layer.draw_rect_filled(pos, auto_positioning.max_position, { 255, 255, 255, 50 });
	}

	bool c_columns::event_control(e_widget_event event) {
		for(std::shared_ptr<i_widget> column : node.childs) if(column->event_control(event)) return true;
		return false;
	}
}