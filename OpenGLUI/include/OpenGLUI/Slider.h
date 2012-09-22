#pragma once
#include "Control.h"
#include "Vector2.h"
#include "Sizeable.h"
#include <functional>

namespace glgui {

/*! \class CSlider
*	\brief Slider Class
*
*	Class used to smoothly change value
*/
class CSlider :
	public CControl,
	public CSizeable
{
protected:
	bool				m_Horizontal;		//!< \protected Horizontal or not state
	bool				m_MousePressed;		//!< \protected Mouse pressed on slider state
	bool				m_PrintValue;		//!< \protected Print value next to slider state
	
	int _CalculateValue (int mx, int my);	//!< \protected Function used to calculate value

public:
	int					Value;					//!< \public Value of slider
	int					RangeMin;				//!< \public Minimum range
	int					RangeMax;				//!< \public Maximum range
	std::tr1::function<void(int)>	Function;	//!< \public Assigned function which take one int parameter

	void Draw ();
	bool MousePress (int x, int y);
	bool MouseRelease (int x, int y);
	void MouseMove (int x, int y);
	void KeyPress (char key);

	/*! \fn void SetHorizontal(bool horizontal)
	*	\brief Set the horizontal of slider
	*	\param horizontal Value to set
	*/
	inline void SetHorizontal (bool horizontal) { m_Horizontal = horizontal; }

	CSlider(void);
	~CSlider(void);
};

}
