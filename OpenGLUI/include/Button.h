#pragma once
#include "control.h"
#include "..\stdafx.h"

namespace glui
{
	class Button :
		public Control
	{
	protected:
		GLuint m_VAOID;
		GLuint m_VBOID;
	public:
		void Draw();

		Button(void);
		~Button(void);
	};
}