#include "Font.h"

#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_OUTLINE_H
#include FT_BITMAP_H

void glui::Font::draw()
{
	FT_Face face = static_cast<FT_Face>(m_Face);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Tex);
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

	FT_UShort currentSize = face->size->metrics.x_ppem;

	if(currentSize != 2000)
		FT_Set_Pixel_Sizes(face, 0, 2000);

	FT_UInt glyph_index;
	glyph_index = FT_Get_Char_Index(face, 'a');
	if(FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT) != 0)
		std::cerr << "blah error" << std::endl;

	if(FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL) != 0)
		std::cerr << "blah inny blad" << std::endl;

	FT_Glyph glyph;

	FT_Get_Glyph(face->glyph, &glyph);

	FT_BitmapGlyph bglyph = (FT_BitmapGlyph)glyph;

	glGenTextures(1, &m_Tex);
	glBindTexture(GL_TEXTURE_2D, m_Tex);
	unsigned char* bitmapa = new unsigned char[face->glyph->bitmap.rows*face->glyph->bitmap.width*4];
	memset(bitmapa, 255, face->glyph->bitmap.rows*face->glyph->bitmap.width*4);

	for(int y = 0; y < face->glyph->bitmap.rows; ++y)
	{
		for(int x = 0; x < face->glyph->bitmap.width; ++x)
		{
			bitmapa[(face->glyph->bitmap.width*4*y)+(x*4)+3] = face->glyph->bitmap.buffer[y*face->glyph->bitmap.width + x];
		}
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmapa);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}