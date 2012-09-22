#include "stdafx.h"
#include "Text.h"
#include "GUI.h"
namespace glgui {

bool CGenericWglText::Init(void)									// Build Our Bitmap Font
{
	HFONT	font;										// Windows Font ID
	HFONT	oldfont;									// Used For Good House Keeping

	m_FontSize = 32;
	m_GlListBase = glGenLists(255);								// Storage For 255 Characters

	font = CreateFont(	-m_FontSize,								// Height Of Font
						0,								// Width Of Font
						0,								// Angle Of Escapement
						0,								// Orientation Angle
						FW_NORMAL,						// Font Weight
						FALSE,							// Italic
						FALSE,							// Underline
						FALSE,							// Strikeout
						EASTEUROPE_CHARSET,				// Character Set Identifier
						OUT_DEFAULT_PRECIS,				// Output Precision
						CLIP_DEFAULT_PRECIS,			// Clipping Precision
						ANTIALIASED_QUALITY,			// Output Quality
						FF_DONTCARE|DEFAULT_PITCH,		// Family And Pitch
						"Consolas");					// Font Name

	oldfont = (HFONT)SelectObject(CGUI::GetSingleton()->GetHDC(), font);           // Selects The Font We Want
	if (!wglUseFontBitmaps(CGUI::GetSingleton()->GetHDC(), 0, 255, m_GlListBase))
		return false;
	SelectObject(CGUI::GetSingleton()->GetHDC(), oldfont);						// Selects The Font We Want
	DeleteObject(font);								// Delete The Font*/

	// Basic version:
//	SelectObject (CGUI::GetSingleton()->GetHDC(), GetStockObject (SYSTEM_FONT)); 
	//if (!wglUseFontBitmaps (CGUI::GetSingleton()->GetHDC(), 0, 255, base))
//		__asm { int 5 };
}

void CGenericWglText::Kill(void)									// Delete The Font List
{
	glDeleteLists(m_GlListBase, 255);							// Delete All 255 Characters
}

/*GLvoid glPrint(const char *fmt, ...)					// Custom GL "Print" Routine
{
	char		text[256];								// Holds Our String
	va_list		ap;										// Pointer To List Of Arguments

	if (fmt == NULL)									// If There's No Text
		return;											// Do Nothing

	va_start(ap, fmt);									// Parses The String For Variables
		vsprintf(text, fmt, ap);						// And Converts Symbols To Actual Numbers
	va_end(ap);											// Results Are Stored In Text

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(base - 32);								// Sets The Base Character to 32
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();										// Pops The Display 

}*/

void CGenericWglText::Print (int32 x, int32 y, const char* text) const
{
	glRasterPos2f(x, y + m_FontSize /* font size */);

	glPushAttrib(GL_LIST_BIT);							// Pushes The Display List Bits
	glListBase(m_GlListBase);								// Sets The Base Character to 32
	glColor4ub(255, 255, 255,255);
	glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);	// Draws The Display List Text
	glPopAttrib();
}

}