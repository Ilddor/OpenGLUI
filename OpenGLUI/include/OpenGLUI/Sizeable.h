#pragma once
#include "Typedefs.h"
#include "Misc.h"
#include "Vector2.h"

namespace glgui {

/*! \class CSizeable
* \brief Sizeable abstract class
*/
class CSizeable
{
protected:
	CVector2<int32>		m_Position;		//!< \protected Vector apearence of object position
	CVector2<int32>		m_Size;			//!< \protected Vector apearence of object size

	inline bool _TestIfInside (int32 mx, int32 my) { return IsPointInRec<int> (CVector2<int32>(mx, my), m_Position, m_Size); }
	//!< \protected Function used to test if point is inside of object
public:
	/*! \fn void SetPosition(const CVector2<int32>& pos)
	*	\brief Set the position of the object
	*	\param pos New position stored in CVector object
	*/
	inline void SetPosition (const CVector2<int32>& pos) { m_Position = pos; }

	/*! \fn void SetSize(const CVector2<int32>& size)
	*	\brief Set the size of the object
	*	\param size New size stored in CVector object
	*/
	inline void SetSize (const CVector2<int32>& size) { m_Size = size; }

	/*! \fn CVector2<int32>& GetPosition (void)
	*	\brief Get the position of the object
	*	\return Const CVector reference
	*/
	inline const CVector2<int32>& GetPosition (void) const { return m_Position; }

	/*! \fn CVector2<int32>& GetSize (void)
	*	\brief Get the size of the object
	*	\return Const CVector reference
	*/
	inline const CVector2<int32>& GetSize (void) const { return m_Size; }
};

}