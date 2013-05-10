#pragma once

namespace glui
{
	class Control
	{
	protected:
		bool m_Focus;
	public:
		void setFocus(bool focus) { m_Focus = focus; };
	
		bool isFocused() { return m_Focus; };

		virtual void Draw() = 0;

		//virtual bool MousePress(int x, int y) = 0;
		//virtual bool MouseRelease(int x, int y) = 0;
		//virtual void MouseMove(int x, int y) = 0;
		//virtual void KeyPress(char key) = 0;
		//virtual void TextEnter(char key) = 0;
	};
}