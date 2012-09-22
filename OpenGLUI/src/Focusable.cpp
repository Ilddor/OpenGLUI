#include "stdafx.h"
#include "Focusable.h"
#include "GUI.h"

namespace glgui {

void CFocusable::SetFocus (bool focus)
{
	m_HasFocus = focus; 
	if (m_HasFocus)
		CGUI::GetSingleton()->SetFocusControl(this);
}

}
