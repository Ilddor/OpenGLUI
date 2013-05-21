#include "Font.h"

#include <iostream>
#include <vector>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H

glui::Font::Page::Glyph glui::Font::getGlyph(unsigned long character)
{
	Page::Glyph glyph;

	auto it = m_Pages.find(m_Size)->second.m_Glyphs.find(character);
	if(it != m_Pages.find(m_Size)->second.m_Glyphs.end())
		return it->second;
	else
	{
		FT_UInt glyph_index;
		FT_Face face = static_cast<FT_Face>(m_Face);
		glyph_index = FT_Get_Char_Index(face, character);
		if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) != 0)
			std::cerr << "blah error" << std::endl;
		if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) != 0)
			std::cerr << "blah inny blad" << std::endl;

		glGenTextures(1, &glyph.m_Texture);
		glBindTexture(GL_TEXTURE_2D, glyph.m_Texture);

		if(face->glyph->bitmap.width == 0)
			glyph.m_Width = face->glyph->metrics.horiAdvance/64;
		else
			glyph.m_Width = face->glyph->bitmap.width;
		//unsigned char* bitmapa = new unsigned char[120*face->glyph->bitmap.width*4];
		std::vector<unsigned char> bitmapa;
		bitmapa.resize(m_Height*face->glyph->bitmap.width*4, 0);
		//memset(bitmapa, 0, sizeof(unsigned char)*120*face->glyph->bitmap.width*4);

		int originY = face->size->metrics.ascender/64;

		if(face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
		{
			for(int y = originY-(face->glyph->metrics.horiBearingY/64); y < (originY-(face->glyph->metrics.horiBearingY/64))+face->glyph->bitmap.rows; ++y)
			{
				for(int x = 0; x < face->glyph->bitmap.width; ++x)
				{
					bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+0] = 0;
					bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+1] = 0;
					bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+2] = 0;
					bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+3] = face->glyph->bitmap.buffer[(y-(originY-(face->glyph->metrics.horiBearingY/64)))*face->glyph->bitmap.width + x];
				}
			}
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapa.data());
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

		bitmapa.clear();

		glBindTexture(GL_TEXTURE_2D, 0);

		m_Pages.find(m_Size)->second.m_Glyphs.insert(std::make_pair(character, glyph));
		return glyph;
	}
}

void glui::Font::loadFromFile(const std::string& filename)
{
	FT_Library library;
	if(FT_Init_FreeType(&library) != 0)
		std::cerr << "Failed to load font: " << filename << " (failed to initialize FreeType)" << std::endl;
	m_Library = library;

	FT_Face face;
	if(FT_New_Face(static_cast<FT_Library>(m_Library), filename.c_str(), 0, &face) != 0)
		std::cerr << "Failed to load font: " << filename << " (failed to create the font face)" << std::endl;

	if(FT_Select_Charmap(face, FT_ENCODING_UNICODE) != 0)
		std::cerr << "Failed to load font: " << filename << " (failed to set the Unicode character set)" << std::endl;

	m_Face = face;

	setSize(60);

	//FT_UShort currentSize = face->size->metrics.x_ppem;

	//if(currentSize != 60)
	//	FT_Set_Pixel_Sizes(face, 0, 60);

	//m_Pages.insert(std::make_pair(60, Page()));

	//*******************************************************************************************************************
	/*
	FT_UInt glyph_index;
	glyph_index = FT_Get_Char_Index(face, L'a');
	if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) != 0)
		std::cerr << "blah error" << std::endl;

	if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) != 0)
		std::cerr << "blah inny blad" << std::endl;

	FT_Glyph glyph;

	FT_Get_Glyph(face->glyph, &glyph);

	FT_BitmapGlyph bglyph = (FT_BitmapGlyph)glyph;

	glGenTextures(1, &m_Tex);
	glBindTexture(GL_TEXTURE_2D, m_Tex);
	unsigned char* bitmapa = new unsigned char[120*face->glyph->bitmap.width*4];
	//memset(bitmapa, 0, sizeof(unsigned char)*120*face->glyph->bitmap.width*4);

	if(face->glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
	{
		for(int y = face->glyph->metrics.vertBearingY/64; y < (face->glyph->metrics.vertBearingY/64)+face->glyph->bitmap.rows; ++y)
		{
			for(int x = 0; x < face->glyph->bitmap.width; ++x)
			{
				bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+0] = 200;
				bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+1] = 200;
				bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+2] = 200;
				bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+3] = face->glyph->bitmap.buffer[y*face->glyph->bitmap.width + x];
			}
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, 120, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapa);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	delete[] bitmapa;

	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void glui::Font::setSize(int size)
{
	m_Size = size;
	if(m_Pages.find(m_Size) == m_Pages.end())
		m_Pages.insert(std::make_pair(m_Size, Page()));

	FT_UShort currentSize = static_cast<FT_Face>(m_Face)->size->metrics.x_ppem;
	if(currentSize != m_Size)
		FT_Set_Pixel_Sizes(static_cast<FT_Face>(m_Face), 0, 60);

	m_Height = static_cast<FT_Face>(m_Face)->size->metrics.height/64;
}

int glui::Font::getSize()
{
	return m_Size;
}