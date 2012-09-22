#include "StdAfx.h"
#include "Frame.h"
#include <algorithm>

namespace glgui {

void CFrame::Draw () 
{ 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(m_Position.X, m_Position.Y, 0.f);

	glColor3ub(70, 100, 120);
	glBegin (GL_QUADS);
		glVertex2i (0, 0);
		glVertex2i (m_Size.X, 0);
		glVertex2i (m_Size.X, m_Size.Y);
		glVertex2i (0, m_Size.Y);
	glEnd();

	std::for_each(m_Controls.begin(), m_Controls.end(), [](CControl* ctrl) { ctrl->Draw(); });
	
	glPopMatrix();
};

bool CFrame::MousePress (int x, int y) 
{
	x -= m_Position.X;
	y -= m_Position.Y;
	std::for_each(m_Controls.begin(), m_Controls.end(), [x,y](CControl* ctrl) { ctrl->MousePress(x,y); });
	return _TestIfInside(x,y);
};

bool CFrame::MouseRelease (int x, int y)
{
	x -= m_Position.X;
	y -= m_Position.Y;
	std::for_each(m_Controls.begin(), m_Controls.end(), [x,y](CControl* ctrl) { ctrl->MouseRelease(x,y); });
	return _TestIfInside(x,y);
}

void CFrame::MouseMove (int x, int y) 
{
	x -= m_Position.X;
	y -= m_Position.Y;
	std::for_each(m_Controls.begin(), m_Controls.end(), [x,y](CControl* ctrl) { ctrl->MouseMove(x,y); });
}

void CFrame::KeyPress (char key) 
{ 
	std::for_each(m_Controls.begin(), m_Controls.end(), [key](CControl* ctrl) { ctrl->KeyPress(key); });
}

void CFrame::TextEnter (char key) 
{ 
	std::for_each(m_Controls.begin(), m_Controls.end(), [key](CControl* ctrl) { ctrl->TextEnter(key); });
}

CFrame::CFrame(void)
{
}


CFrame::~CFrame(void)
{
}

}
