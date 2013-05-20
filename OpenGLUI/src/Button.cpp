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

	std::array<GLfloat, 8> tex_coords = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticesBackground.size(), verticesBackground.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_tex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*tex_coords.size(), tex_coords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);

	//_setVBO();
	Vector2<GLfloat> pos = m_Position;
	Font::Page::Glyph glyph;

	glyph = font.getGlyph(L'P');
	setSize(Vector2<GLfloat>(glyph.m_Width, 60));
	glBindTexture(GL_TEXTURE_2D, glyph.m_Texture);
	glDrawArrays(GL_QUADS, 0, 4);

	setPosition(pos);

	glBindTexture(GL_TEXTURE_2D, 0);

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
	m_Function = function;
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
	m_tex = 0;

	GLuint cos = 0;

	glGenVertexArrays(1, &cos);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_vertices);
	glGenBuffers(1, &m_colors);
	glGenBuffers(1, &m_tex);

	font.loadFromFile("arial.ttf");

	_setVBO();
}


glui::Button::~Button()
{
	glDeleteBuffers(1, &m_vertices);
	glDeleteBuffers(1, &m_colors);
	glDeleteBuffers(1, &m_tex);
	glDeleteVertexArrays(1, &m_VAOID);
}
