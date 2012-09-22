#include "stdafx.h"
#include "Button.h"
#include "Misc.h"

namespace glgui {

void CButton::_SetCaptionPosition()
{
	CVector2<int> LabelOffset;
	LabelOffset.Y = m_Size.Y / 2 - 20;
	// TEMP : znalezc sposob na znajdowanie szerokosci i centrowanie napisu \
	powinno to byc w klasie CLabel
	LabelOffset.X = 5;
	m_Caption.SetPosition (m_Position + LabelOffset);
}

void CButton::SetPosition (const CVector2<int>& pos)
{
	m_Position = pos;
	_SetCaptionPosition();
}

void CButton::SetSize (const CVector2<int>& size)
{
	m_Size = size;
	_SetCaptionPosition();
}

void CButton::Draw()
{
	if (!(m_DisplayOptions.Visible))
		return;

	glDisable(GL_TEXTURE_2D);
	glLineWidth (4);

	int X = m_Position.X;
	int Y = m_Position.Y;
	int Width = m_Size.X;
	int Height = m_Size.Y;
	
	// Tlo
	glColor3f (0.3f, 0.3f, 0.3f);
	glBegin(GL_QUADS);
		glVertex2i (X, Y);
		glVertex2i (X + Width, Y);
		glVertex2i (X + Width, Y + Height);
		glVertex2i (X, Y + Height);
	glEnd();
	
	// Ramka
	glBegin (GL_LINES);
		if (m_DisplayOptions.Clicked)
			glColor3f (0.1f, 0.1f, .1f);
		else
			glColor3f (0.7f, 0.7f, 0.7f);
		// Gora
		glVertex2i (X, Y);
		glVertex2i (X + Width, Y);
		//Lewo
		glVertex2i (X, Y);
		glVertex2i (X, Y+Height);
		
		if (m_DisplayOptions.Clicked)
			glColor3f (0.7f, 0.7f, 0.7f);
		else
			glColor3f (0.1f, 0.1f, .1f);
		//Prawo
		glVertex2i (X + Width, Y + Height);
		glVertex2i (X, Y + Height);
		//Dol
		glVertex2i (X + Width, Y + Height);
		glVertex2i (X + Width, Y);
	glEnd();
	
	glColor3ub(255,255,255);

	m_Caption.Draw();
}
bool CButton::MouseRelease(int mouseX, int mouseY)
{
	if (m_DisplayOptions.Clicked)
	{
		m_DisplayOptions.Clicked = false;
		if (_TestIfInside(mouseX, mouseY))
		{
			if (!m_Function._Empty())
				m_Function();
			return true;
		}
		else
			return false;
	}
	else 
		return false;
}

bool CButton::MousePress (int mouseX, int mouseY)
{
	if (_TestIfInside(mouseX, mouseY))
	{
		m_DisplayOptions.Clicked = true;
		return true;
	}
	return false;
}

CButton::CButton(void)
{
	m_Size.X = 120; m_Size.Y = 50;
	m_DisplayOptions.Clicked = false;
	m_DisplayOptions.Enabled = true;
	m_DisplayOptions.Visible = true;
}


CButton::~CButton(void)
{
}

}
