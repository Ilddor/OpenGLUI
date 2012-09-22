#pragma once
#include "Label.h"
#include "Focusable.h"
#include "Sizeable.h"
#include <functional>

namespace glgui {

/*! \class CTextbox
*	\brief Textbox class
*
*	Class used to take text from keyboard and send it to the assigned function as parameter
*/
class CTextbox :
	public CLabel,
	public CFocusable
{
protected:
	std::tr1::function<void(const std::string&)>	m_Function;		//!< \protected Pointer to assigned function
	bool											m_AutoClear;	//!< \protected Auto clear on gain focus
	CLabel										m_Caption;			//!< \protected Text of object

public:
	bool MousePress (int mouseX, int mouseY);
	bool MouseRelease (int mouseX, int mouseY);
	void MouseMove (int mouseX, int mouseY) { }
	void TextEnter (char key);
	void Draw ();

	void SetPosition (const CVector2<int>& pos);
	void SetSize (const CVector2<int>& size);

	/*! \fn void SetAutoClear(bool autoClear)
	*	\brief Set the autoclear option
	*	\param autoClear Value to set
	*/
	inline void SetAutoClear (bool autoClear) { m_AutoClear = autoClear; }

	/*! \fn void SetFunction(const std::tr1::function<void(const std::string&)>& function)
	*	\brief Assign the function to the object
	*	\param function Const reference to function with one const std::string parameter as reference
	*/
	inline void SetFunction (const std::tr1::function<void(const std::string&)>& function) { m_Function = function; }

	CTextbox(void);
	~CTextbox(void);
};

}
