#pragma once

#include <set>
#include <memory>

#include "Control.h"

namespace glui
{
	class GUI
	{
	protected:
		int					m_ScreenWidth;
		int					m_ScreenHeight;

		std::set<Control*>	m_Controls;
		Control*			m_ControlWithFocus;

		void _ClearFocus();
	public:
		void Draw();

		void AddControl(Control* control);

		GUI(void);
		~GUI(void);
	};
}