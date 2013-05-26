#pragma once
#include "../stdafx.h"
#include "Vector2.h"
#include "Drawable.h"

namespace glui
{
	class Control:
		public Drawable
	{
	protected:
		bool m_Focus;

		bool _isPointIn(Vector2<GLfloat>& point)
		{
			return (point >= m_Position && point <= (m_Position+m_Size));
		};
	public:
		void setFocus(bool focus) { m_Focus = focus; };
	
		bool isFocused() { return m_Focus; };

		virtual bool MousePress(int x, int y) = 0;
		virtual bool MouseRelease(int x, int y) = 0;
		virtual void MouseMove(int x, int y) = 0;
		virtual void KeyPress(char key) = 0;
		virtual void TextEnter(char key) = 0;
	};
}