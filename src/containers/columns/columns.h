#pragma once
#include <containers/group/group.h>

namespace null::gui {
	class c_columns : public i_container {
	public:
		struct style_t {
			float column_padding{ 10.f };
		} style{ };

	public:
		class c_column : public i_container {
		public:
			struct style_t {
				float widget_padding{ 10.f };
			} style{ };

		public:
			c_column() : i_container("column") { }

			void append_auto_positioning(i_widget* widget) override;
			bool event_control(e_widget_event event) override;
		};

	public:
		c_columns(int split) : i_container("column") {
			node.childs.resize(split);
			std::ranges::generate(node.childs, []() { return std::make_shared<c_column>(); });
		}

		i_widget* at(int i) { return node.childs[i].get(); }

		void append_auto_positioning(i_widget* widget) override;

		void setup() override;
		void draw() override;

		bool event_control(e_widget_event event) override;
	};
}