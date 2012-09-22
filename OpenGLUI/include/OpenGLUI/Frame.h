#pragma once
#include "Control.h"
#include "Typedefs.h"
#include "Sizeable.h"
#include <unordered_set>

namespace glgui {

/*! \class CFrame
* \brief Frame class
*
*	Class of frame in which you can put controls
*/
class CFrame :
	public CControl,
	public CSizeable
{
protected:
	std::unordered_set<CControl*> m_Controls;	//!< \protected Set of pointers to controls

public:
	/*! \fn T* AddControl()
	*	\brief Automaticaly create and add control to frame
	*	\return T* Pointer to created control
	*/
	template<typename T> inline T* AddControl () { T* Temp = new T; m_Controls.insert(Temp); return Temp; }

	/*! \fn void AddControlByPtr(CControl* ctrl)
	*	\brief Add control to the frame
	*	\param ctrl Pointer to your control
	*/
	inline void AddControlByPtr (CControl* ctrl) { m_Controls.insert(ctrl); }

	void Draw ();
	bool MousePress (int x, int y);
	bool MouseRelease (int x, int y);
	void MouseMove (int x, int y);
	void KeyPress (char key);
	void TextEnter (char key);

	CFrame(void);
	virtual ~CFrame(void);
};

}
