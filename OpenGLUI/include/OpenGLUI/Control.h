#pragma once
#include "Vector2.h"

namespace glgui {

/*! \class CControl
* \brief Control abstract class
*/
class CControl
{
protected:
	/*! \struct _SDisplayOptions
	*	\brief Options structure
	*/
	struct _SDisplayOptions
	{
		bool Clicked;			//!< \public Clicked option
		bool Visible;			//!< \public Visible option
		bool Enabled;			//!< \public Enabled option
	} m_DisplayOptions;		//!< \protected Display options of object
public:
	//virtual void SetPosition (const CVector2d<int>& pos) abstract;
	//virtual CVector2d<int> GetPosition (void) const abstract;

	/*! \fn void Draw()
	*	\brief Draw an object in the window
	*	This method is being called automatically when object is added to CGUI class
	*/
	virtual void Draw () { }

	/*! \fn void MousePress(int x, int y)
	*	\brief Sends a mouse press event position to the object
	*	This method is being called automatically when object is added to CGUI class
	*	\param x An x position of event
	*	\param y An y position of event
	*	\return A bool that say if mouse pressed this button
	*/
	virtual bool MousePress (int x, int y) { return false; };

	/*! \fn void MouseRelease(int x, int y)
	*	\brief Sends a mouse release event position to the object
	*	This method is being called automatically when object is added to CGUI class
	*	\param x An x position of event
	*	\param y An y position of event
	*	\return A bool that say if mouse released over this button
	*/
	virtual bool MouseRelease (int x, int y) { return false; }

	/*! \fn void MouseMove(int x, int y)
	*	\brief Sends a new position of mouse to the object
	*	This method is being called automatically when object is added to CGUI class
	*	\param x An x position of mouse
	*	\param y An y position of mouse
	*/
	virtual void MouseMove (int x, int y) { }

	/*! \fn void KeyPress(char key)
	*	\brief Sends a key press event to the object
	*	This method is being called automatically when object is added to CGUI class
	*	\param key Code of pressed key
	*/
	virtual void KeyPress (char key) { }

	/*! \fn void TextEnter(char key)
	*	\brief Sends a text enter event to the object
	*	This method is being called automatically when object is added to CGUI class
	*	\param key Code of pressed key
	*/
	virtual void TextEnter (char key) { };


	CControl(void) { }		//!< \public Default constructor
	virtual ~CControl(void) { }		//!< \public Default virtual constructor
};

}
