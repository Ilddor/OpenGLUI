#pragma once

#include <string>
#include "../stdafx.h"

namespace glui
{
	class Font
	{
	protected:
		void*	m_Library;
		void*	m_Face;
		GLuint	m_Tex;
	public:
		void draw();
		void loadFromFile(const std::string& filename);
	};
}