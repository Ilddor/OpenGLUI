#pragma once
#include "Typedefs.h"

namespace glgui {

// Interface for all Text-drawing classes
/*! \class IText
* \brief Text class
*
*	Class used to print the text on the screen
*/
class IText
{
public:
	/*! \fn bool Init()
	*	\brief Build the font
	*	\return bool Information that font has been built
	*/
	virtual bool Init() abstract;

	/*! \fn void Kill()
	*	\brief Delete the built font
	*/
	virtual void Kill() abstract;

	/*! \fn void Print (int32 x, int32 y, const char* text)
	*	\brief Print the text on screen with built font
	*	\param x X position of text
	*	\param y Y position of text
	*	\param text Text to build
	*/
	virtual void Print (int32 x, int32 y, const char* text) const abstract;
};

// Pretty straightforward implementation using WGL
/*! \class CGenericWglText
* \brief GenericWglText class
*/
class CGenericWglText :
	public IText
{
private:
	uint32	m_GlListBase;	//!< \private List of characters
	int32	m_FontSize;		//!< \private Font size of text

public:
	bool Init();
	void Kill();
	void Print (int32 x, int32 y, const char* text) const;
};

}