#pragma once

#include <set>
#include <memory>

#include "Control.h"

namespace glui
{
	class GUI
	{
	protected:
		int									m_ScreenWidth;
		int									m_ScreenHeight;

		std::set<std::shared_ptr<Control>>	m_Controls;
		std::weak_ptr<Control>				m_ControlWithFocus;

		void _ClearFocus();
	public:
		GUI(void);
		~GUI(void);
	};
}