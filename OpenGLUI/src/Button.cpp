#include "Button.h"


void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);
	glEnableVertexAttribArray(m_VAOID);

	glColor3f(1.f, 1.f, 1.f);
	glDrawArrays(GL_LINES, 0, 2);
}

glui::Button::Button(void)
{
	m_VAOID = 0;
	m_VBOID = 0;

	GLuint cos = 0;

	glGenVertexArrays(1, &cos);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_VBOID);

	GLfloat tmp[6] = {-1.f, 0.f, 0.f, 1.f, 0.f, 0.f};

	glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, tmp, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


glui::Button::~Button(void)
{
	glDeleteBuffers(1, &m_VBOID);
	glDeleteVertexArrays(1, &m_VAOID);
}
