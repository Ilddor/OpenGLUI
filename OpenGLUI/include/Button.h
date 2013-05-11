#pragma once
#include "..\stdafx.h"
#include "Control.h"

namespace glui
{
	class Button :
		public Control
	{
	protected:
		GLuint m_VAOID;
		GLuint m_vertices;
		GLuint m_colors;

		void _setVBO();
	public:
		void Draw();

		void setPosition(GLfloat x,GLfloat y);
		void setPosition(Vector2<GLfloat> position);
		void setSize(GLfloat width, GLfloat height);
		void setSize(Vector2<GLfloat> size);

		Vector2<GLfloat> getPosition();
		Vector2<GLfloat> getSize();

		Button();
		~Button();
	};
}