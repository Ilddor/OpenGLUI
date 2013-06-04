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
		bool			m_AutoSize;

		void _setVBO();
	public:
		void Draw();

		bool isUsingTextures();

		void setText(const std::wstring& text);
		void setFont(Font* font);
		void setFontSize(int size);
		void setAutoSize(bool value);

		std::wstring getText();

		Label();
		~Label();
	};
}