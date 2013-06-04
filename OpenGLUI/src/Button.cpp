#include "Button.h"

#include <string>
#include <iostream>
#include <array>

void glui::Button::_setVBO()
{
	glBindVertexArray(m_VAOID);

	std::array<GLfloat, 8> verticesBackground = {
		m_Position.X, m_Position.Y,
		m_Position.X+m_Size.X, m_Position.Y,
		m_Position.X+m_Size.X, m_Position.Y+m_Size.Y,
		m_Position.X, m_Position.Y+m_Size.Y
	};

	std::array<GLfloat, 12> colors = {
		1.f, 1.f, 1.f,
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
	};

	std::array<GLfloat, 8> tex_coords = {
		0.f, 0.f,
		1.f, 0.f,
		1.f, 1.f,
		0.f, 1.f
	};


	glBindBuffer(GL_ARRAY_BUFFER, m_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticesBackground.size(), verticesBackground.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colors.size(), colors.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_tex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*tex_coords.size(), tex_coords.data(), GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	Vector2<GLfloat> tmp = m_Position;
	tmp += Vector2<GLfloat>(2.f,2.f);

	m_Label.setPosition(tmp);

	tmp = m_Size;
	tmp -= Vector2<GLfloat>(4.f,4.f);

	m_Label.setSize(tmp);
	m_Label.setFontSize(m_Size.Y);
}

void glui::Button::Draw()
{
	glBindVertexArray(m_VAOID);

	glBindTexture(GL_TEXTURE_2D, m_tex);

	glDrawArrays(GL_QUADS, 0, 4);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	//glFlush();

	glUniform1f(2, 1.f);	//FIXME: change it to automatic -.-
	m_Label.Draw();
}

bool glui::Button::isUsingTextures()
{
	return false;
}

void glui::Button::setFunction(std::function<void()> function)
{
	m_Function = function;
}

void glui::Button::setCaption(const std::wstring& caption)
{
	m_Label.setText(caption);
}

void glui::Button::setFont(Font* font)
{
	m_Label.setFont(font);
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

	m_Label.setAutoSize(false);

	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_vertices);
	glGenBuffers(1, &m_colors);
	glGenBuffers(1, &m_tex);

	glBindVertexArray(0);

	_setVBO();
}


glui::Button::~Button()
{
	glDeleteBuffers(1, &m_vertices);
	glDeleteBuffers(1, &m_colors);
	glDeleteBuffers(1, &m_tex);
	glDeleteVertexArrays(1, &m_VAOID);

	glDeleteTextures(1, &m_tex);
}
