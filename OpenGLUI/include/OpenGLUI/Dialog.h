#pragma once
#include "Focusable.h"
#include "Sizeable.h"
#include "Typedefs.h"

#include <array>

namespace glgui {

class CButton;

/*! \class CDialog
* \brief Dialog class
*
* Class used to create dialog window
*/
class CDialog :
	public CFocusable,
	public CSizeable
{
protected:
	 uint32 m_Style;	//!< \protected Style of object represented by uint32
	 
	 std::array<CButton*, 4> m_Buttons;	//!< \protected Array of buttons

public:
	/*! \enum Return Codes
	*/
	enum ERetCodes
	{
		RET_OK = 0,		//!< OK
		RET_CANCEL,		//!< CANCEL
		RET_YES,		//!< YES
		RET_NO			//!< NO
	};

	/*! \fn uint32 ShowModal()
	*	\brief Add control to the CGUI class and focus on it.
	*	\return uint32
	*/
	uint32 ShowModal ();
	void Draw();

	bool MousePress (int x, int y);
	bool MouseRelease (int x, int y);

	CDialog(void);
	~CDialog(void);
};

}
