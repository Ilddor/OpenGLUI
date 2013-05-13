#include "Button.h"

#include <string>
#include <iostream>
#include <array>

void glui::Button::_setVBO()
{
	std::array<GLfloat, 8> verticesBackground = {
		m_Position.X, m_Position.Y,
		m_Position.X+m_Size.X, m_Position.Y,
		m_Position.X+m_Size.X, m_Position.Y+m_Size.Y,
		m_Position.X, m_Position.Y+m_Size.Y
	};

	std::array<GLfloat, 12> colors = {
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.3f, 0.3f, 0.3f,
		0.3f, 0.3f, 0.3f
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticesBackground.size(), verticesBackground.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);

	//_setVBO();

	glDrawArrays(GL_QUADS, 0, 4);

	/*std::array<GLfloat, 12> colors = {
		0.8f, 0.8f, 0.8f,
		0.2f, 0.2f, 0.2f,
		0.2f, 0.2f, 0.2f,
		0.2f, 0.2f, 0.2f
	};

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	//glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void glui::Button::setFunction(std::function<void()> function)
{
	std::swap(m_Function, function);
}

bool glui::Button::MousePress(int x, int y)
{
	if(_isPointIn(Vector2<GLfloat>(x,y)))
	{
		if(!m_Function._Empty())
			m_Function();
		return true;
	}
	else
		return false;
}

bool glui::Button::MouseRelease(int x, int y)
{
	return false;
}

glui::Button::Button()
{
	m_VAOID = 0;
	m_vertices = 0;
	m_colors = 0;

	GLuint cos = 0;

	glGenVertexArrays(1, &cos);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_vertices);
	glGenBuffers(1, &m_colors);

	_setVBO();
}


glui::Button::~Button()
{
	glDeleteBuffers(1, &m_vertices);
	glDeleteBuffers(1, &m_colors);
	glDeleteVertexArrays(1, &m_VAOID);
}
