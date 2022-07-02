#include <null-gui.h>
#include <containers/container.h>

namespace null::gui {
	void i_container::append_auto_size() {
		size = auto_positioning.max_position - pos;
	}

	void i_container::setup_auto_positioning() {
		auto_positioning = auto_positioning_t{ 0.f, pos };
	}

	void i_container::append_auto_positioning(i_widget* widget) {
		auto_positioning.max_position = math::max(auto_positioning.max_position, widget->pos + widget->size);
		auto_positioning.next_position.y += widget->size.y;
	}

	void i_container::setup() {
		setup_auto_positioning();

		for(std::shared_ptr<i_widget>& widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;
			
			if(!(widget->flags & e_widget_flags::ignore_auto_positioning))
				widget->pos = auto_positioning.next_position;	
			
			widget->setup();
			
			if(!(widget->flags & e_widget_flags::ignore_auto_positioning))
				append_auto_positioning(widget.get());
		}

		if(container_flags & e_container_flags::auto_size) {
			append_auto_size();
		}
	}

	void i_container::draw() {
		std::vector<i_widget*> draw_on_top_layer{ };

		for(std::shared_ptr<i_widget>& widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;

			if(widget->flags & e_widget_flags::draw_on_top_layer) draw_on_top_layer.push_back(widget.get());
			else widget->draw();
		}

		std::ranges::for_each(draw_on_top_layer, [](i_widget* widget) { widget->draw(); });
	}
}