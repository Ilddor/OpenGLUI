#pragma once
#include "../stdafx.h"
#include "Vector2.h"

namespace glui
{
	class Control
	{
	protected:
		bool m_Focus;

		Vector2<GLfloat> m_Position;
		Vector2<GLfloat> m_Size;

		bool _isPointIn(Vector2<GLfloat>& point) { return (point >= m_Position && point <= m_Size); };
	public:
		void setFocus(bool focus) { m_Focus = focus; };
	
		bool isFocused() { return m_Focus; };

		virtual void Draw() = 0;

		void setPosition(const GLfloat x, const GLfloat y) { m_Position = Vector2<GLfloat>(x,y); };
		void setPosition(const Vector2<GLfloat> position) { m_Position = position; };
		void setSize(const GLfloat width, GLfloat height) { m_Size = Vector2<GLfloat>(width,height); };
		void setSize(const Vector2<GLfloat> size) { m_Size = size; };

		Vector2<GLfloat> getPosition() { return m_Position; };
		Vector2<GLfloat> getSize() { return m_Size; };

		virtual bool MousePress(int x, int y) = 0;
		virtual bool MouseRelease(int x, int y) = 0;
		virtual void MouseMove(int x, int y) = 0;
		virtual void KeyPress(char key) = 0;
		virtual void TextEnter(char key) = 0;
	};
}