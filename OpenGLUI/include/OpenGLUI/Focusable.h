#pragma once
#include "Control.h"

namespace glgui {

/*! \class CFocusable
* \brief Focusable abstract class
*/
class CFocusable :
	virtual public CControl
{
protected:
	bool m_HasFocus;	//!< \protected Focus state

public:
	/*! \fn void SetFocus(bool focus)
	*	\brief Set the focus on object
	*	\param focus Bool value of new focus state
	*/
	virtual void SetFocus (bool focus);

	/*! \fn bool GetFocus()
	*	\brief Get the focus state on object
	*	\return Current focus state on object
	*/
	virtual inline bool GetFocus () const { return m_HasFocus; }


	CFocusable(void) { }			//!< \public Default constructor
	virtual ~CFocusable(void) { }	//!< \public Default virtual destructor
};

}
