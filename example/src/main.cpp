#include <iostream>
#include <mutex>
#include <null-gui.h>
#include <renderers/directx9/directx9.h>

null::render::directx9::c_window window{ };

void create_ui() {
	{
		auto window{ new null::gui::c_window{ "window 1", { 100 }, { 200, 300 } } };
		null::gui::c_window::add_window(window);
		{
			window->add_widget(new null::gui::c_button{ "window button 1" });

			auto column{ new null::gui::c_columns{ 3 } };
			{
				column->at(0)->add_widget(new null::gui::c_button{ "0" });
				column->at(0)->add_widget(new null::gui::c_button{ "1" });

				column->at(1)->add_widget(new null::gui::c_button{ "0" });
				column->at(1)->add_widget(new null::gui::c_button{ "1" });

				column->at(2)->add_widget(new null::gui::c_button{ "0" });
				column->at(2)->add_widget(new null::gui::c_button{ "1" });
			}
			window->add_widget(column);

			window->add_widget(new null::gui::c_button{ "window button 2" });

			auto group{ new null::gui::c_group{ "group" } };
			window->add_widget(group);
			{
				group->add_widget(new null::gui::c_button{ "group button 1" });
				group->add_widget(new null::gui::c_button{ "group button 2" });
				group->add_widget(new null::gui::c_button{ "group button 3" });
			}
		}
	}

	{
		auto window{ new null::gui::c_window{ "window 2", { 310, 100 }, { 60 } } };
		null::gui::c_window::add_window(window);
	}

	{
		auto window{ new null::gui::c_window{ "window 3", { 380, 100 }, { 60 } } };
		null::gui::c_window::add_window(window);
	}
}

void destroy_ui() {
	null::gui::i_widget::widgets.clear();
	null::gui::c_window::window_stack.clear();
}

#define debug_print_widget(widget) \
widgets.data.push_back({#widget, { 255, 100, 100 }}); \
widgets.data.push_back({std::format(" = "), { }}); \
widgets.data.push_back({std::format("{}\n", null::gui::i_widget::widgets[null::widget] ? null::gui::i_widget::widgets[null::widget]->name : "empty"), { 100, 255, 100 }});

void main_loop() {
	null::render::begin_frame(window);
	null::gui::begin_frame();
	null::input::begin_frame(window);
	{
		null::render::multicolor_text_t widgets{ };

		debug_print_widget(e_widget_state::active);
		debug_print_widget(e_widget_state::hovered);
		debug_print_widget(e_widget_state::focused);

		null::render::background_layer.draw_text(widgets, { });
		null::render::background_layer.draw_text(std::format("fps: {:3.0f}", 1.f / window.time_data.delta_time), { window.get_window_size().x, 10 }, { }, null::e_text_flags{ -null::e_text_flags::aligin_right | -null::e_text_flags::aligin_center_y | -null::e_text_flags::outline });
	}
	null::gui::end_frame();
	null::render::end_frame();
	null::render::setup_draw_data();
}

int main(HINSTANCE instance) {
	window = null::render::directx9::c_window{ instance };

	try {
		null::render::global_atlas.add_font_from_file_ttf("C:\\Windows\\fonts\\Tahoma.ttf", 13.f);
		window.callbacks.add<int(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, null::input::wnd_proc);
		window.callbacks.add<int(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, null::gui::wnd_proc);

		null::input::keys[null::e_key_id::num_0].callbacks.add<void()>(null::e_key_state::up, create_ui);
		null::input::keys[null::e_key_id::num_1].callbacks.add<void()>(null::e_key_state::up, destroy_ui);

		window.create();
		null::gui::initialize();

		window.main_loop(main_loop);

		window.destroy();
	} catch(std::exception exp) {
		std::cout << exp.what() << std::endl;
	}
}