#include "Label.h"

#include "../stdafx.h"
#include <array>

void glui::Label::_setVBO()
{
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


	glBindBuffer(GL_ARRAY_BUFFER, m_Vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticesBackground.size(), verticesBackground.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_Colors);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*colors.size(), colors.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*tex_coords.size(), tex_coords.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if(m_Font != nullptr && !m_Text.empty())
	{
		glBindTexture(GL_TEXTURE_2D, m_Texture);
		int x = 0;
		int y = 0;
		Font::Page::Glyph glyph;
		for(auto character: m_Text)
		{
			glyph = m_Font->getGlyph(character, m_FontSize);
			x += glyph.m_Width+2;	//2 is for offset between characters
		}
		y = glyph.m_Height;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		x = 0;
		for(auto character: m_Text)
		{
			glyph = m_Font->getGlyph(character, m_FontSize);
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, 0, glyph.m_Width, glyph.m_Height, GL_RGBA, GL_UNSIGNED_BYTE, glyph.m_Bytes.data());
			x += glyph.m_Width+2;
		}
	}
}

void glui::Label::Draw()
{
	glBindVertexArray(m_VAOID);

	glBindTexture(GL_TEXTURE_2D, m_Texture);

	glDrawArrays(GL_QUADS, 0, 4);
}

bool glui::Label::isUsingTextures()
{
	return true;
}

void glui::Label::setText(const std::wstring& text)
{
	m_Text = text;
	_setVBO();
}

void glui::Label::setFont(Font* font)
{
	m_Font = font;
	_setVBO();
}

void glui::Label::setFontSize(int size)
{
	m_FontSize = size;
	GLfloat width, height;
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
	glGetTexLevelParameterfv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
	m_Size = Vector2<GLfloat>(width, height);
	_setVBO();
}

std::wstring glui::Label::getText()
{
	return m_Text;
}

glui::Label::Label()
{
	m_VAOID = 0;
	m_Vertices = 0;
	m_Colors = 0;
	m_TextureCoords = 0;
	m_FontSize = 30;
	m_Font = nullptr;

	glGenVertexArrays(1, &m_VAOID);
	glBindVertexArray(m_VAOID);

	glGenBuffers(1, &m_Vertices);
	glGenBuffers(1, &m_Colors);
	glGenBuffers(1, &m_TextureCoords);

	glGenTextures(1, &m_Texture);

	_setVBO();
}

glui::Label::~Label()
{
	glDeleteBuffers(1, &m_Vertices);
	glDeleteBuffers(1, &m_Colors);
	glDeleteBuffers(1, &m_TextureCoords);
	glDeleteVertexArrays(1, &m_VAOID);
	
	glDeleteTextures(1, &m_Texture);
}