#pragma once
#include "Typedefs.h"
#include "Singleton.h"
#include "Control.h"
#include "Input.h"
#include "Text.h"

#include <set>
#include <string>
#include <list>
#include <map>
#include <fstream>

namespace glgui {

class CFocusable;

/*! \class CGUI
*	\brief GUI class
*
*	Class used draw, take events and send them to the controls, etc. Most important class, it is doing lots of thing automatically
*/
class CGUI :
	public CSingleton<CGUI>
{
protected:
	uint16								m_ScreenWidth;		//!< \protected Width of the screen in pixels
	uint16								m_ScreenHeight;		//!< \protected Height of the screen in pixels

	std::list<std::string>				m_Console;			//!< \protected List of string in console
	std::string							m_TypeLine;			//!< \protected String to write text to console

	std::list<std::string>				m_LastCommands;		//!< \protected List of last command strings
	std::list<std::string>::iterator	m_LastCommand;		//!< \protected List iterator of last command string

	std::map<std::string, std::string>	m_DebugFields;		//!< \protected Don't know yet
	//TODO std::map<std::string, float&>		m_DebugWatches;

	std::ofstream						m_LogFile;			//!< \protected Hook to log file
	std::set<CControl*>					m_Controls;			//!< \protected Set of added controls
	CFocusable*							m_ControlWithFocus;	//!< \protected Pointer to control with focus

	HDC									m_HDC;				//!< \protected Don't know yet

	IText*								m_TextProvider;		//!< \protected Pointer to font

	void _ZeroFocus (void);				//!< \protected Function used to clear focus
	void _PushAndSetGLStates (void);	//!< \protected Function used to set needed states in OpenGL
	void _PopGLStates (void);			//!< \protected Function used to unset states in OpenGL
	CControl* _FindControl (const SMouseEvent& event); //!< \protected Function used for dealing with mouse events.
	
public:
	/*! \fn void Init(HDC hdc, uint32 xSize, uint32 ySize)
	*	\brief Initialize the interface
	*	\param hdc
	*	\param xSize X size of window
	*	\param ySize Y size of window
	*/
	void Init (HDC hdc, uint32 xSize, uint32 ySize);

	/*! \fn void Print(const std::string& msg, const int32 x, const int32 y)
	*	\brief Print text on the screen
	*	\param msg Text to print
	*	\param x X position of text
	*	\param y Y position of text
	*/
	void Print (const std::string& msg, const int32 x, const int32 y);

	/*! \fn void Message(const std::string& msg)
	*	\brief Send message to the console
	*	\param msg Text to send
	*/
	void Message (const std::string& msg);

	/*! \fn void DrawConsole()
	*	\brief Draw the console
	*/
	void DrawConsole (void);

	/*! \fn void Draw()
	*	\brief Draw whole interface
	*/
	void Draw (void);

	/*! \fn void KeyPress(char key)
	*	\brief Send the pressed key to adequate control
	*	\param key Code of pressed key
	*/
	void KeyPress (char key);

	/*! \fn void TextEnter(char key)
	*	\brief Send the text to adequate control
	*	\param key Code of pressed key
	*/
	void TextEnter (char key);

	/*! \fn void MousePress(const SMouseEvent& event)
	*	\brief Send the mouse press event to adequate control
	*	\param event Mouse event reference
	*/
	void MousePress (const SMouseEvent& event);

	/*! \fn void MouseRelease(const SMouseEvent& event)
	*	\brief Send the mouse release event to adequate control
	*	\param event Mouse event reference
	*/
	void MouseRelease (const SMouseEvent& event);

	/*! \fn void MouseMove(const SMouseEvent& event)
	*	\brief Send the mouse move event to adequate control
	*	\param event Mouse event reference
	*/
	void MouseMove (const SMouseEvent& event);

	void SetDebugField (const std::string& ident, const std::string& val);
	void SetDebugField (const std::string& ident, const float32 val);
	void SetDebugField (const std::string& ident, const int32 val);
	//TODO void SetDebugWatch (const std::string& ident, const float32& ref);
	//TODO void SetDebugWatch (const std::string& ident, const int32& ref);

	/*! \fn void DrawDebug()
	*	\brief Draw debug informations
	*/
	void DrawDebug (void);

	inline HDC GetHDC () { return m_HDC; }

	/*! \fn T* AddControl(const T& object)
	*	\brief Add control to the interface
	*	\param object Reference to control to add
	*	\return T* Pointer to added control
	*/
	template<typename T> T* AddControl (const T& object)
	{
		// U¿ywam dynamic_cast do sprawdzenia, czy na pewno T dziedziczy po CControl
		T* TempPtr = new T(object);
		CControl* TempBasePtr = dynamic_cast<CControl*>(TempPtr);
		if (TempBasePtr)
			m_Controls.insert (TempBasePtr);
		else
		{
			delete TempPtr;
			TempPtr = 0;
		}
		return TempPtr;
	}

	/*! \fn T* AddControl()
	*	\brief Add control to the interface template form
	*	\return T* Pointer to added control
	*/
	template<typename T> T* AddControl ()
	{
		T* TempPtr = new T();
		m_Controls.insert (TempPtr);
		return TempPtr;
	}

	/*! \fn void AddControlByPtr(CControl* ctrl)
	*	\brief Add control to the interface by pointer
	*	\param ctrl Pointer to control to add
	*/
	inline void AddControlByPtr (CControl* ctrl) { m_Controls.insert(ctrl); }

	/*! \fn void DeleteControl(CControl* pointer)
	*	\brief Delete the control from the interface
	*	\param pointer Pointer to contorl to delete
	*/
	void DeleteControl (CControl* pointer);

	/*! \fn void SetFocusControl(CFocusable* pointer)
	*	\brief Set focus to the control
	*	\param pointer Pointer to contorl to set focus at
	*/
	void SetFocusControl (CFocusable* pointer) { m_ControlWithFocus = pointer; }

	CGUI(void);
	~CGUI(void);
};

}
