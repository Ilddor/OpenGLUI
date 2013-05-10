#include "Gui.h"
#include "..\stdafx.h"

void glui::GUI::_ClearFocus()
{
	if(m_ControlWithFocus != nullptr)
		m_ControlWithFocus->setFocus(false);
	m_ControlWithFocus = nullptr;
}

void glui::GUI::Draw()
{
	for(auto it: m_Controls)
	{
		it->Draw();
	}
}

void glui::GUI::AddControl(Control* control)
{
	m_Controls.insert(control);
}

glui::GUI::GUI(void)
{
	glewInit();
}


glui::GUI::~GUI(void)
{
}
