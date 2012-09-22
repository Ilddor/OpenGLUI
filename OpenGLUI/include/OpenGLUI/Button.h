#pragma once
#include "Control.h"
#include "Sizeable.h"
#include "Label.h"
#include <functional>

namespace glgui {

/*! \class CButton
* \brief Button class
*
* Class used to assign actions to the text button
*/
class CButton :
	public CControl,
	public CSizeable
{
protected: 
	CLabel							m_Caption;		//!< \protected Button caption
	std::tr1::function<void(void)>	m_Function;		//!< \protected Function pointer

	void _SetCaptionPosition ();	//!< \protected Function used to set the caption position
public:
	/*! \fn void SetPosition(const CVector2<int>& pos)
	*	\brief Set the position of the object
	*	\param pos New position stored in CVector object
	*/
	void SetPosition (const CVector2<int>& pos);
	/*! \fn void SetSize(const CVector2<int>& size)
	*	\brief Set the size of the object
	*	\param size New size stored in CVector object
	*/
	void SetSize (const CVector2<int>& size);
	/*! \fn void SetCaption(const std::string& caption)
	*	\brief Set the caption of the button
	*	\param caption New caption
	*/
	void SetCaption (const std::string& caption) { 	m_Caption.SetCaption (caption); }
	// Do czasu wprowadzenia nowego standardu VS nie mozna zamienic lambdy na wskaznik w prosty sposob
	// Dlatego u¿ywam std::tr1::function
	// Pod g++ nalezaloby to zmieniæ na lambdy, 4.5 juz to obsluguje

	/*! \fn void SetFunction(const std::tr1::function<void(void)>& func)
	*	\brief Assign function to the button
	*	\param func Reference of function pointer
	*/
	void SetFunction (const std::tr1::function<void(void)>& func) { m_Function = func; }
	bool MousePress (int mouseX, int mouseY);
	bool MouseRelease (int mouseX, int mouseY);
	void KeyPress (char key) { }
	/*! \fn void Draw()
	*	\brief Draw an object in the window
	*	This method is being called automatically when object is added to CGUI class
	*/
	void Draw();

	CButton(void);		//!< \public Default constructor
	~CButton(void);		//!< \public Default destructor
};

}
