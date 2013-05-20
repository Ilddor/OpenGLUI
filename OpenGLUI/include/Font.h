#pragma once

#include <string>
#include <map>
#include "../stdafx.h"

namespace glui
{
	class Font
	{
	protected:
		void*	m_Library;
		void*	m_Face;
		int		m_Size;
		int		m_Height;	//real height that bitmap should have

		GLuint m_Tex;
	public:
		struct Page
		{
			struct Glyph
			{
				GLuint			m_Texture;
				unsigned int	m_Width;
			};
			std::map<unsigned int, Glyph> m_Glyphs;
		};

		Page::Glyph getGlyph(unsigned long character);
		void loadFromFile(const std::string& filename);

		void setSize(int size);

		int getSize();

	protected:
		std::map<unsigned int, Page>	m_Pages;
	};
}