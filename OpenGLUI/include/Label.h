#pragma once

#include <string>

#include "Control.h"
#include "Font.h"

namespace glui
{
	class Label:
		public Drawable
	{
	protected:
		GLuint			m_VAOID;
		GLuint			m_Vertices;
		GLuint			m_Colors;
		GLuint			m_TextureCoords;
		GLuint			m_Texture;

		std::wstring	m_Text;
		Font*			m_Font;
		int				m_FontSize;

		void _setVBO();
	public:
		void Draw();

		bool isUsingTextures();

		void setText(const std::wstring& text);
		void setFont(Font* font);
		void setFontSize(int size);

		std::wstring getText();

		Label();
		~Label();
	};
}