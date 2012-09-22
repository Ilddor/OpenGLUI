#include "stdafx.h"
#include "Label.h"
#include "Text.h"
#include "GUI.h"

namespace glgui {

void CLabel::Draw()
{
	CGUI::GetSingleton()->Print(m_Caption.c_str(), m_Position.X,  m_Position.Y);
}

}

