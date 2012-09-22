#include "stdafx.h"
#include "Misc.h"
#include "Textbox.h"
#include "GUI.h"

namespace glgui {

using namespace std;

bool CTextbox::MousePress (int mouseX, int mouseY)
{
	return IsPointInRec<int> (CVector2<int>(mouseX, mouseY), m_Position, m_Size);
}

bool CTextbox::MouseRelease (int mouseX, int mouseY)
{
	if (IsPointInRec<int> (CVector2<int>(mouseX, mouseY), m_Position, m_Size))
	{
		SetFocus(true);
		return true;
	}
	return false;
}

void CTextbox::Draw()
{
	glPushAttrib (GL_STENCIL_TEST | GL_TEXTURE_2D);

	glDisable (GL_TEXTURE_2D);
	glLineWidth (2);
	glColor3f (0.3f, 0.3f, 0.3f);
	int X = m_Position.X;
	int Y = m_Position.Y;
	int Width = m_Size.X;
	int Height = m_Size.Y;

	// ramka
	glBegin (GL_LINE_LOOP);
		glVertex2i (X, Y);
		glVertex2i (X + Width, Y);
		glVertex2i (X + Width, Y + Height);
		glVertex2i (X, Y + Height);
	glEnd();

	// pole do stencil testu
	glEnable (GL_STENCIL_TEST);
	glClearStencil(0x0);
	glClear(GL_STENCIL_BUFFER_BIT);
	glStencilFunc (GL_ALWAYS, 0x1, 0x1);
	glStencilOp (GL_REPLACE, GL_REPLACE, GL_REPLACE);
	glColorMask (false, false, false, false);
	glBegin (GL_QUADS);
		glVertex2i (X+1, Y+1);
		glVertex2i (X+Width-1, Y+1);
		glVertex2i (X+Width-1, Y+Height-1);
		glVertex2i (X+1, Y+Height-1);
	glEnd();
	glColorMask (true,true,true,true);

	// tekst
	glEnable (GL_TEXTURE_2D);
	glStencilFunc (GL_EQUAL, 0x1, 0x1);
	glStencilOp (GL_KEEP, GL_KEEP, GL_KEEP);
	//TODO CGraphics::GetSingleton()->GetWindow().Draw (m_Caption);
	
	glPopAttrib ();
}

void CTextbox::SetPosition (const CVector2<int>& pos)
{
	m_Caption.SetPosition (pos);
	m_Position = pos;
}

void CTextbox::TextEnter (char key)
{
	string Temp = m_Caption.GetCaption();
	switch (key)
	{
	case 13:
		if (!m_Function._Empty())
			m_Function (Temp);
		if (m_AutoClear)
			m_Caption.SetCaption ("");
		break;
	case 8:
		if (!Temp.empty()) // BACKSPACE
		{
			Temp.pop_back();
			m_Caption.SetCaption (Temp);
		}
		break;
	default:
		m_Caption.SetCaption(Temp+key);
		break;
	}
}

CTextbox::CTextbox(void)
{
	m_Position(0,0);
	m_Size(100, 36);
	m_AutoClear = false;
}


CTextbox::~CTextbox(void)
{
}

}
