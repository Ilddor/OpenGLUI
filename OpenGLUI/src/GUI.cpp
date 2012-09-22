#include "stdafx.h"
#include "GUI.h"
#include "Typedefs.h"
#include "Focusable.h"
#include "Text.h"

namespace glgui {

using namespace std;
using boost::lexical_cast;

//-----------------------------------------------------------------------------------------------
void CGUI::Init(HDC hdc, uint32 xSize, uint32 ySize)
{
	m_HDC = hdc;
	m_ScreenWidth = xSize;
	m_ScreenHeight = ySize;
	m_TextProvider->Init();
}
//-----------------------------------------------------------------------------------------------
void CGUI::DeleteControl (CControl* pointer)
{
	m_Controls.erase (pointer);
}
//-----------------------------------------------------------------------------------------------
void CGUI::Print (const string& msg, const int32 x, const int32 y)
{
	m_TextProvider->Print(x, y, msg.c_str());
}
//-----------------------------------------------------------------------------------------------
void CGUI::_ZeroFocus(void)
{
	if (m_ControlWithFocus)
		m_ControlWithFocus->SetFocus (false);
	m_ControlWithFocus = 0;
}
//-----------------------------------------------------------------------------------------------
void CGUI::_PushAndSetGLStates (void)
{
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	glLoadIdentity();
	glOrtho (0, m_ScreenWidth, m_ScreenHeight, 0, -1, 1);

	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
	glLoadIdentity();
}
//-----------------------------------------------------------------------------------------------
void CGUI::_PopGLStates (void)
{
	glMatrixMode (GL_PROJECTION);
	glPushMatrix ();
	glMatrixMode (GL_MODELVIEW);
	glPushMatrix ();
}
//-----------------------------------------------------------------------------------------------
void CGUI::Message (const string& msg)
{
	uint32 Sz = msg.size();
	for (uint32 i = 0; i < Sz; ++i)
	{
		uint32 Pos = msg.find_first_of('\n', i);
		if (Pos == string::npos)
		{
			m_Console.push_back(msg.substr(i));
			break;
		}
		else
		{
			m_Console.push_back (msg.substr (i, Pos-i));
			i = Pos+1;
		}
	}
	m_LogFile << msg << endl;
	if (msg.size()>=1)
	if (*(msg.end()-1)=='\n')
	{
		m_Console.push_back (string(""));
	}
}
//-----------------------------------------------------------------------------------------------
void CGUI::DrawConsole()
{
	_PushAndSetGLStates();
	glEnable(GL_TEXTURE_2D);
	uint16 Count = 0;
	for (list<string>::const_reverse_iterator It = m_Console.rbegin(); (It != m_Console.rend()) && (Count<20); It++)
	{
		Print ((*It), 0, 736-Count*24);
		Count++;
	}
	Print (string("> ") + m_TypeLine, 0, 760);
	_PopGLStates();
}
//-----------------------------------------------------------------------------------------------
unsigned int Hash( void *p )
{
   return reinterpret_cast<unsigned int>( p );
}
//-----------------------------------------------------------------------------------------------
void CGUI::Draw ()
{
	_PushAndSetGLStates();
	glEnable(GL_TEXTURE_2D);
	for (auto It = m_Controls.begin(); It != m_Controls.end(); It++)
	{
		(*It)->Draw();
	}
	_PopGLStates();
}
//-----------------------------------------------------------------------------------------------
void CGUI::KeyPress (char key)
{
	//TODO: jesli nawet mamy jakas kontrolke, powinnismy
	// obsluzyc tabulator do przelaczania focusu
	if (m_ControlWithFocus == 0)
	{
		switch (key)
		{
		case Key::Return:
			m_Console.push_back (m_TypeLine);
			//TODO : callback func m_Game->Invoke (m_Console.back());
			if (m_LastCommands.empty() || m_TypeLine != m_LastCommands.front())
				m_LastCommands.push_front(m_TypeLine);
			m_LastCommand = m_LastCommands.end();
			m_TypeLine.clear();
			break;

		case Key::Up:
			if (!m_LastCommands.empty())
			{
				if (m_LastCommand != m_LastCommands.end())
				{
					m_LastCommand++;
					if (m_LastCommand == m_LastCommands.end())
						m_LastCommand--;			
				}
				else
					m_LastCommand = m_LastCommands.begin();

				m_TypeLine = *m_LastCommand;
			}
			break;

		case Key::Down:
			if (!m_LastCommands.empty())
			{
				if (m_LastCommand == m_LastCommands.end())
					m_LastCommand = m_LastCommands.begin();
				if (m_LastCommand != m_LastCommands.begin())
					m_LastCommand--;

				m_TypeLine = *m_LastCommand;
			}
			break;

		case Key::End:

		case Key::Home:
		case Key::Insert:
		case Key::Delete:
			break;

		case Key::RAlt:
		case Key::LAlt:
		case Key::RShift:
		case Key::LShift:
		case Key::RSystem:
		case Key::LSystem:
			break;
		}
	}
	else 
		m_ControlWithFocus->KeyPress(key);
}
//-----------------------------------------------------------------------------------------------
void CGUI::TextEnter (char key)
{
	if (m_ControlWithFocus == 0)
	{
		switch (key) 
		{
		case 8: // Backspace
			if (m_TypeLine.size()>=1)
				m_TypeLine.erase(m_TypeLine.end()-1);
			break;
		case 13:
		case 96: // Tylda
			break;
		default:
			m_TypeLine += (char)(key);
			break;
		}
	}
	else 
		m_ControlWithFocus->TextEnter(key);
}
//-----------------------------------------------------------------------------------------------
CControl* CGUI::_FindControl(const SMouseEvent& event)
{
	_PushAndSetGLStates();
	glDisable (GL_TEXTURE_2D);
	glStencilOp (GL_KEEP, GL_KEEP, GL_INCR);
	glClearColor (0.f, 0.f, 0.f, 0.f);
	glClear (GL_COLOR_BUFFER_BIT);
	glClearStencil (0);
	glEnable(GL_STENCIL_TEST);
	for (auto It = m_Controls.begin(); It != m_Controls.end(); It++)
	{
		glClear (GL_STENCIL_BUFFER_BIT);	
		glStencilFunc(GL_ALWAYS, 1, 1);
		(*It)->Draw();
		glStencilFunc(GL_LESS, 0, 0xFF);

		CControl* Ptr = (*It);
		unsigned int PtrVal = reinterpret_cast<unsigned int>(Ptr);
		GLubyte* PtrValBuf = reinterpret_cast<GLubyte*>(&PtrVal);
		glColor4ubv (PtrValBuf);

		glBegin (GL_QUADS);
			glVertex2i (0,0);
			glVertex2i (m_ScreenWidth,0);
			glVertex2i (m_ScreenWidth,m_ScreenHeight);
			glVertex2i (0,m_ScreenHeight);
		glEnd();
	}

	unsigned char Bytes[4];
	glReadBuffer (GL_BACK);
	glReadPixels(event.X, m_ScreenHeight - event.Y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, Bytes);
	//TEMP
	Bytes[3] = 0;
	unsigned int PtrVal = (Bytes[0]) + (Bytes[1]<<8) + (Bytes[2]<<16) + (Bytes[3]<<24);
	CControl* Ptr = reinterpret_cast<CControl*>(PtrVal);

	glDisable (GL_STENCIL_TEST);
	_PopGLStates();

	return Ptr;
}
//-----------------------------------------------------------------------------------------------
void CGUI::MousePress (const SMouseEvent& event)
{
	CControl* Ptr = _FindControl(event);

	if (Ptr != 0)
		Ptr->MousePress(event.X, event.Y);
	else
		_ZeroFocus();
}
void CGUI::MouseRelease (const SMouseEvent& event)
{
	for (auto It = m_Controls.begin(); It != m_Controls.end(); It++)
	{
		(*It)->MouseRelease(event.X, event.Y);
	}
}
void CGUI::MouseMove (const SMouseEvent& event)
{
	for (auto It = m_Controls.begin(); It != m_Controls.end(); It++)
	{
		(*It)->MouseMove(event.X, event.Y);
	}
}
//-----------------------------------------------------------------------------------------------
void CGUI::SetDebugField (const string& ident, const string& val)
{
	m_DebugFields[ident] = val;
}
void CGUI::SetDebugField (const string& ident, const float val)
{
	m_DebugFields[ident] = lexical_cast<string>(val);
}
void CGUI::SetDebugField (const string& ident, const int val)
{
	m_DebugFields[ident] = lexical_cast<string>(val);
}
//-----------------------------------------------------------------------------------------------
void CGUI::DrawDebug (void)
{
	glEnable(GL_TEXTURE_2D);
	glColor4ub (255, 255, 0, 255);
	uint16 Counter = 0;
	for (map<string, string>::iterator It = m_DebugFields.begin(); It!=m_DebugFields.end(); It++)
	{
		Counter++;
		Print ((*It).first, 0, Counter*24);
		Print (string (": ")+(*It).second, 256, Counter*24);
	}
}
//-----------------------------------------------------------------------------------------------
CGUI::CGUI()
{
	m_ControlWithFocus = 0;
	m_LastCommand = m_LastCommands.end();
	m_LogFile.open ("guilog.txt", ios::out | ios::trunc);
	m_TextProvider = new CGenericWglText();
}

CGUI::~CGUI(void)
{
	m_LogFile.close();
	for (auto It = m_Controls.begin(); It != m_Controls.end(); It++)
	{
		delete (*It);
	}
	m_Controls.clear ();
	m_TextProvider->Kill();
}

}
