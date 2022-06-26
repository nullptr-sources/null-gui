#include <null-gui.h>
#include <containers/container.h>

namespace null::gui {
	void c_container::append_auto_positioning(c_widget* widget) {
		widget->pos = auto_positioning.next_position;
		auto_positioning.next_position.y += widget->size.y;
	}

	void c_container::draw() {
		std::vector<c_widget*> draw_on_top_layer{ };

		for(std::shared_ptr<c_widget> widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;

			widget->setup();

			if(!(widget->flags & e_widget_flags::ignore_auto_positioning))
				append_auto_positioning(widget.get());

			if(widget->flags & e_widget_flags::draw_on_top_layer) draw_on_top_layer.push_back(widget.get());
			else widget->draw();
		}

		std::ranges::for_each(draw_on_top_layer, [](c_widget* widget) { widget->draw(); });
	}
}