#include "Button.h"

#include <string>
#include <iostream>

void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);

	glDrawArrays(GL_TRIANGLES, 0, 3);
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

	GLfloat tmp[9] = {-1.f,0.f,0.f, 1.f,0.f,0.f, 0.f,1.f,0.f};
	GLfloat color[9] = {1.f,0.f,0.f, 0.f,0.f,1.f, 0.f,1.f,0.f};

	glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, tmp, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*9, color, GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


glui::Button::~Button(void)
{
	glDeleteBuffers(1, &m_vertices);
	glDeleteBuffers(1, &m_colors);
	glDeleteVertexArrays(1, &m_VAOID);
}
