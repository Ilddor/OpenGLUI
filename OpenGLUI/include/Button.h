#pragma once
#include "..\stdafx.h"
#include <functional>

#include "Control.h"
#include "Label.h"

namespace glui
{
	class Button :
		public Control
	{
	protected:
		GLuint					m_VAOID;
		GLuint					m_vertices;
		GLuint					m_colors;
		GLuint					m_tex;

		//Label					m_Label;

		std::function<void()>	m_Function;

		void _setVBO();
	public:
		void Draw();

		bool isUsingTextures();

		void setFunction(std::function<void()> function);

		bool MousePress(int x, int y);
		bool MouseRelease(int x, int y);
		void MouseMove(int x, int y) {};
		void KeyPress(char key) {};
		void TextEnter(char key) {};

		Button();
		~Button();
	};
}