#pragma once

#include "../stdafx.h"

#include <list>
#include <memory>

#include "Control.h"

namespace glui
{
	class GUI
	{
	protected:
		int					m_ScreenWidth;
		int					m_ScreenHeight;

		GLuint				m_VertexShader;
		GLuint				m_FragmentShader;
		GLuint				m_Program;
		GLint				m_UsingTexturesUniform;

		std::list<Drawable*>	m_Objects;
		std::list<Control*>	m_Controls;
		Control*			m_ControlWithFocus;

		glm::mat4			m_Projection;
		glm::mat4			m_View;
		GLint proj;
		GLint view;

		void _ClearFocus();
	public:
		void Draw();

		void AddDrawableObject(Drawable* object);

		void setProjectionMatrix(glm::mat4 projection);
		void setViewMatrix(glm::mat4 view);

		void MousePress(int x, int y);

		GUI();
		~GUI();
	};
}