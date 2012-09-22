#pragma once
#include "Control.h"
#include "Sizeable.h"
#include <string>

namespace glgui {

/*! \class CLabel
* \brief Text label class
*
* Class used to storage texts
*/
class CLabel :
	public CControl,
	public CSizeable
{
protected:
	CVector2<int>	m_Position;	 //!< \protected Object position
	std::string		m_Caption;	 //!< \protected Stored string

public:
	/*! \fn void SetPosition(const CVector2<int>& pos)
	*	\brief Set the position of the object
	*	\param pos New position stored in CVector object
	*/
	inline virtual void			SetPosition (const CVector2<int>& pos) { m_Position = pos; }
	/*! \fn void SetCaption(const std::string& caption)
	*	\brief Set the object's string
	*	\param caption String to storage
	*/
	virtual void				SetCaption (const std::string& caption) { m_Caption = caption; }
	/*! \fn void GetCaption()
	*	\brief Get the object's string
	*	\return Const string reference
	*/
	virtual const std::string&	GetCaption () const { return m_Caption; }
	/*! \fn void Draw()
	*	\brief Draw an object in the window
	*/
	void						Draw ();
};

}
