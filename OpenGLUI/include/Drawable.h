#pragma once
#include "Vector2.h"

namespace glui
{
	class Drawable
	{
	protected:
		Vector2<GLfloat> m_Position;
		Vector2<GLfloat> m_Size;

		virtual void _setVBO() = 0;
	public:
		virtual void Draw() = 0;

		void setPosition(const GLfloat x, const GLfloat y)
		{
			m_Position = Vector2<GLfloat>(x,y);
			_setVBO();
		}

		void setPosition(const Vector2<GLfloat> position)
		{
			m_Position = position;
			_setVBO();
		}

		void setSize(const GLfloat width, GLfloat height)
		{
			m_Size = Vector2<GLfloat>(width,height);
			_setVBO();
		}

		void setSize(const Vector2<GLfloat> size)
		{
			m_Size = size;
			_setVBO();
		}

		virtual bool isUsingTextures() = 0;

		Vector2<GLfloat> getPosition() { return m_Position; }
		Vector2<GLfloat> getSize() { return m_Size; }
	};
}