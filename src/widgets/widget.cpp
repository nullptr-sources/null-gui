#include <null-gui.h>
#include <widgets/widget.h>

namespace null::gui {
	std::vector<c_widget*> c_widget::node_t::parent_node() {
		std::vector<c_widget*> node{ };

		if(parent) {
			node = parent->node.parent_node();
			node.push_back(parent);
		}

		return node;
	}

	std::vector<c_widget*> c_widget::node_t::child_node() {
		std::vector<c_widget*> node{ };

		for(std::shared_ptr<c_widget> child : childs) {
			auto child_node = child->node.child_node();
			node.push_back(child.get());
			node.insert(node.end(), child_node.begin(), child_node.end());
		}

		return node;
	}

	void c_widget::add_widget(c_widget* widget) {
		widget->node.parent = this;
		node.childs.push_back(std::shared_ptr<c_widget>(widget));
	}

	void c_widget::draw() {
		std::vector<c_widget*> draw_on_top_layer{ };
		for(std::shared_ptr<c_widget> widget : node.childs) {
			if(!(widget->flags & e_widget_flags::visible)) continue;
			
			if(widget->flags & e_widget_flags::draw_on_top_layer) draw_on_top_layer.push_back(widget.get());
			else widget->draw();
		}

		std::ranges::for_each(draw_on_top_layer, [](c_widget* widget) { widget->draw(); });
	}

	void c_widget::on_focused() {
		state |= e_widget_state::focused;
		widgets[e_widget_state::focused] = this;

		for(c_widget* parent : node.parent_node() | std::views::reverse)
			parent->on_child_focused(this);

		callbacks.call<void()>(e_widget_callbacks::on_focused);
	}

	void c_widget::on_lost_focus(c_widget* new_focused_widget) {
		if(new_focused_widget == widgets[e_widget_state::focused]) return;

		state &= ~e_widget_state::focused;
		widgets[e_widget_state::focused] = nullptr;

		for(c_widget* parent : node.parent_node() | std::views::reverse)
			parent->on_child_lost_focus(this, new_focused_widget);

		callbacks.call<void()>(e_widget_callbacks::on_lost_focus);
	}

	void c_widget::on_mouse_move() {
		callbacks.call<void()>(e_widget_callbacks::on_mouse_move);
	}

	void c_widget::on_mouse_enter() {
		state |= e_widget_state::hovered;
		widgets[e_widget_state::hovered] = this;

		callbacks.call<void()>(e_widget_callbacks::on_mouse_enter);
	}

	void c_widget::on_mouse_exit() {
		state &= ~e_widget_state::hovered;
		widgets[e_widget_state::hovered] = nullptr;

		callbacks.call<void()>(e_widget_callbacks::on_mouse_exit);
	}

	void c_widget::on_mouse_key_down() {
		state |= e_widget_state::active;
		widgets[e_widget_state::active] = this;

		callbacks.call<void()>(e_widget_callbacks::on_mouse_key_down);
	}

	void c_widget::on_mouse_key_up() {
		state &= ~e_widget_state::active;
		widgets[e_widget_state::active] = nullptr;

		callbacks.call<void()>(e_widget_callbacks::on_mouse_key_up);
	}

	bool c_widget::event_control(e_widget_event msg) {
		for(std::shared_ptr<c_widget> child_widget : node.childs | std::views::reverse) {
			if(child_widget->flags & e_widget_flags::visible && child_widget->event_control(msg)) return true;
		}

		switch(msg) {
			case e_widget_event::mouse_move: {
				if(can_hovered() || state & e_widget_state::active) {
					if(!(state & e_widget_state::hovered)) {
						if(widgets[e_widget_state::hovered]) {
							widgets[e_widget_state::hovered]->on_mouse_exit();
						}

						on_mouse_enter();
					}

					on_mouse_move();

					return true;
				}
			} break;
			case e_widget_event::mouse_key_down: {
				if(state & e_widget_state::hovered && !widgets[e_widget_state::active]) {
					on_mouse_key_down();

					if(widgets[e_widget_state::focused] && widgets[e_widget_state::focused] != this) {
						widgets[e_widget_state::focused]->on_lost_focus(this);
					}

					if(!(state & e_widget_state::focused)) {
						on_focused();
					}

					return true;
				}
			} break;
			case e_widget_event::mouse_key_up: {
				if(state & e_widget_state::active) {
					on_mouse_key_up();

					return true;
				}
			} break;
		}

		return false;
	}
}