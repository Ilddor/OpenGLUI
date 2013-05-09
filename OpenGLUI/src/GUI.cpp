#include "Gui.h"

void glui::GUI::_ClearFocus()
{
	if(m_ControlWithFocus._Get() != nullptr)
		m_ControlWithFocus._Get()->setFocus(false);
	m_ControlWithFocus.reset();
}

glui::GUI::GUI(void)
{
}


glui::GUI::~GUI(void)
{
}
