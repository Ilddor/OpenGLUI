#pragma once

#include <string>
#include <vector>
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

		void _setSize(int size);
	public:
		struct Page
		{
			struct Glyph
			{
				std::vector<unsigned char>	m_Bytes;
				unsigned int				m_Width;
				unsigned int				m_Height;
			};
			std::map<unsigned int, Glyph> m_Glyphs;
		};

		Page::Glyph getGlyph(unsigned long character, int size);

		void loadFromFile(const std::string& filename);

	protected:
		std::map<unsigned int, Page>	m_Pages;
	};
}