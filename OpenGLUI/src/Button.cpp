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
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f,
		1.f, 0.f, 1.f
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
	std::swap(m_function, function);
}

void glui::Button::setPosition(GLfloat x, GLfloat y)
{
	m_Position.X = x;
	m_Position.Y = y;

	_setVBO();
}

void glui::Button::setPosition(Vector2<GLfloat> position)
{
	m_Position = position;

	_setVBO();
}

void glui::Button::setSize(GLfloat width, GLfloat height)
{
	m_Size.X = width;
	m_Size.Y = height;

	_setVBO();
}

void glui::Button::setSize(Vector2<GLfloat> size)
{
	m_Size = size;

	_setVBO();
}

glui::Vector2<GLfloat> glui::Button::getPosition()
{
	return m_Position;
}

glui::Vector2<GLfloat> glui::Button::getSize()
{
	return m_Size;
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
