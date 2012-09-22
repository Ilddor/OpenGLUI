#include "stdafx.h"
#include "Slider.h"
#include "GUI.h"

namespace glgui {

void CSlider::Draw ()
{
	glDisable (GL_TEXTURE_2D);
	glLineWidth (3);

	// T³o
	glColor3f (0.2f, 0.2f, 0.2f);
	glBegin (GL_QUADS);
		glVertex2i (m_Position.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y + m_Size.Y);
		glVertex2i (m_Position.X, m_Position.Y+m_Size.Y);
	glEnd();

	// Linia
	glColor3f (0.5f, 0.5f, 0.5f);
	glBegin (GL_LINES);
		if (m_Horizontal)
		{
			glVertex2i (m_Position.X, m_Position.Y+m_Size.Y/2);
			glVertex2i (m_Position.X+m_Size.X, m_Position.Y+m_Size.Y/2);
		}
		else
		{
			glVertex2i (m_Position.X+m_Size.X/2, m_Position.Y);
			glVertex2i (m_Position.X+m_Size.X/2, m_Position.Y+m_Size.Y);
		}
	glEnd();

	// Ramka
	glColor3f (0.3f, 0.3f, 0.3f);
	glBegin (GL_LINE_LOOP);
		glVertex2i (m_Position.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y + m_Size.Y);
		glVertex2i (m_Position.X, m_Position.Y+m_Size.Y);
	glEnd();

	// Punkt
	glColor3f (0.1f, 0.3f, 0.7f);
	if (m_Horizontal)
		glPointSize (m_Size.Y/2);
	else
		glPointSize (m_Size.X/2);
	
	glBegin (GL_POINTS);
		float Pos;
		if (m_Horizontal)
		{	
			Pos = ((float)(Value) / (RangeMax-RangeMin)) * m_Size.X + m_Position.X;
			glVertex2i (Pos, m_Position.Y+m_Size.Y/2);
		}
		else
		{
			Pos = ((float)(Value) / (RangeMax-RangeMin)) * m_Size.Y + m_Position.Y;
			glVertex2i (m_Position.X+m_Size.X/2, Pos);
		}
	glEnd();

	if (m_PrintValue)
		CGUI::GetSingleton()->Print (boost::lexical_cast<std::string, int>(Value), m_Position.X+m_Size.X, m_Position.Y);
}

int CSlider::_CalculateValue(int mx, int my)
{
	if (m_Horizontal)
		return (RangeMax-RangeMin) * ((float)(mx-m_Position.X)/m_Size.X) + RangeMin;
	else
		return(RangeMax-RangeMin) * ((float)(my-m_Position.Y)/m_Size.Y) + RangeMin;
}

bool CSlider::MousePress (int x, int y)
{
	if ((x >= m_Position.X) && (x <= m_Position.X + m_Size.X)
		&& (y >= m_Position.Y) && (y <= m_Position.Y+m_Size.Y))
	{
		int OldValue = Value;
		Value = _CalculateValue(x,y);
		if (OldValue != Value && !Function._Empty())
			Function(Value);
		m_MousePressed = true;
		m_PrintValue = true;
		return true;
	}
	return false;
}

bool CSlider::MouseRelease (int x, int y)
{
	m_MousePressed = false;
	m_PrintValue = false;
	return false;
}

void CSlider::MouseMove (int x, int y)
{
	int OldValue = Value;

	if (m_MousePressed)
	{
		Value = _CalculateValue(x,y);
		Value = (Value <= RangeMax) ? Value : RangeMax;
		Value = (Value >= RangeMin) ? Value : RangeMin;
	}

	if (OldValue != Value && !Function._Empty())
		Function(Value);
}

void CSlider::KeyPress (char key)
{
}

CSlider::CSlider(void)
{
	m_MousePressed = false;
	m_PrintValue = false;
	RangeMin = 0;
	RangeMax = 100;
	Value = 35;
}


CSlider::~CSlider(void)
{
}

}
