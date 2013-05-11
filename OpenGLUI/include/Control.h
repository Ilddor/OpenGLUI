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
	public:
		void setFocus(bool focus) { m_Focus = focus; };
	
		bool isFocused() { return m_Focus; };

		virtual void Draw() = 0;

		virtual void setPosition(GLfloat x, GLfloat y) = 0;
		virtual void setPosition(Vector2<GLfloat> position) = 0;
		virtual void setSize(GLfloat width, GLfloat height) = 0;
		virtual void setSize(Vector2<GLfloat> size) = 0;

		virtual Vector2<GLfloat> getPosition() = 0;
		virtual Vector2<GLfloat> getSize() = 0;

		//virtual bool MousePress(int x, int y) = 0;
		//virtual bool MouseRelease(int x, int y) = 0;
		//virtual void MouseMove(int x, int y) = 0;
		//virtual void KeyPress(char key) = 0;
		//virtual void TextEnter(char key) = 0;
	};
}