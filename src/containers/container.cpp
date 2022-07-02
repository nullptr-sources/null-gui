#include <null-gui.h>
#include <containers/container.h>

namespace null::gui {
	void i_container::setup_auto_positioning() {
		auto_positioning.next_position = pos;
		auto_positioning.max_position = 0.f;
	}

	void i_container::append_auto_positioning(i_widget* widget) {
		auto_positioning.next_position.y += widget->size.y;
		auto_positioning.max_position = math::max(auto_positioning.max_position, auto_positioning.next_position);
	}

	void i_container::setup() {
		setup_auto_positioning();

		for(std::shared_ptr<i_widget> widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;
			
			widget->pos = auto_positioning.next_position;
			widget->setup();

			if(!(widget->flags & e_widget_flags::ignore_auto_positioning))
				append_auto_positioning(widget.get());
		}
	}

	void i_container::draw() {
		std::vector<i_widget*> draw_on_top_layer{ };

		for(std::shared_ptr<i_widget> widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;

			if(widget->flags & e_widget_flags::draw_on_top_layer) draw_on_top_layer.push_back(widget.get());
			else widget->draw();
		}

		std::ranges::for_each(draw_on_top_layer, [](i_widget* widget) { widget->draw(); });
	}
}