#include <null-gui.h>

namespace null::gui {
	//@credits: https://github.com/KN4CK3R/OSHGui
	int wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
		e_widget_event widget_msg{ };

		switch(msg) { //transform WM message in e_widget_msg
			case WM_MOUSEMOVE:
				widget_msg = e_widget_event::mouse_move;
				break;
			
			case WM_LBUTTONDOWN:
			case WM_RBUTTONDOWN:
				widget_msg = e_widget_event::mouse_key_down;
				break;

			case WM_LBUTTONUP:
			case WM_RBUTTONUP:
				widget_msg = e_widget_event::mouse_key_up;
				break;
		}

		if(c_widget::widgets[e_widget_state::active] && c_widget::widgets[e_widget_state::active]->event_control(widget_msg)) return -1;
		if(c_widget::widgets[e_widget_state::focused] && c_widget::widgets[e_widget_state::focused]->event_control(widget_msg)) return -1;

		for(std::shared_ptr<c_window> window : c_window::window_stack | std::views::reverse) {
			if(window->event_control(widget_msg))
				return -1;
		}

		switch(widget_msg) {
			case e_widget_event::mouse_key_down: {
				if(c_widget::widgets[e_widget_state::focused])
					c_widget::widgets[e_widget_state::focused]->on_lost_focus(nullptr);
			} break;

			case e_widget_event::mouse_move: {
				if(c_widget::widgets[e_widget_state::hovered])
					c_widget::widgets[e_widget_state::hovered]->on_mouse_exit();
			} break;
		}

		return -1;
	}
}