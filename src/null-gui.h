#pragma once

#include <null-render.h>
#include <null-input.h>
#include <null-sdk.h>

#include <widgets/button/button.h>

#include <containers/columns/columns.h>
#include <containers/popup/popup.h>
#include <containers/group/group.h>
#include <containers/window/window.h>

#include <ranges>

namespace null::gui {
	inline render::c_draw_list gui_layer{ };

	static void initialize() {
		render::custom_layers.push_back(&gui_layer);
	}

	static void begin_frame() {
	}

	static void end_frame() {
		std::ranges::for_each(c_window::window_stack, [](std::shared_ptr<c_window> window) {
			if(!(window->flags & e_widget_flags::visible)) return;
			window->handle();
			});
	}

	int wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param);
}