#pragma once
#include "Typedefs.h"
#include "Control.h"
#include "Button.h"
#include "Label.h"
#include "Textbox.h"
#include "Input.h"
#include "Focusable.h"
#include <list>

namespace glgui
{

/*! \class CComboBox
* \brief ComboBox class
*
* Class used to assign values to strings
*/
class CComboBox :
	public CFocusable,
	public CSizeable
{
protected:
	/*! \class CComboLabel
	* \brief Overloaded Label class
	*
	* Class used to storage assigned values and stirngs
	*/
	class CComboLabel : public CLabel
	{
	public:
		int		m_Value;	//!< \public Stored value

		void Draw();
		bool MousePress(int mouseX, int mouseY);
		bool MouseRelease(int mouseX, int mouseY);
	};

	/*! \class CComboButton
	* \brief Overloaded Button class
	*
	* Class used to drop the list of options
	*/
	class CComboButton : public CButton
	{
	public:
		void Draw();
	}m_DropButton;		//!< \protected Drop button

	std::list<CComboLabel*>				m_List;			//!< \protected List of pointers to stored options
	std::list<CComboLabel*>::iterator	m_Selected;		//!< \protected Iterator of pointer to currently seleceted option
	bool								m_Dropped;		//!< \protected State of list, dropped or not
	bool								m_IsSelected;	//!< \protected State of iterator, already selected or not

	void _Sort();	//!< \protected Function used to sort positions of member options
public:
	// Overloaded member functions
	void SetSize(const CVector2<int>& size);
	void SetPosition(const CVector2<int>& pos);
		
	/*! \fn int GetSelectedValue()
	*	\brief Get the value of currently selected option
	*	\return Int value
	*/
	int GetSelectedValue() { return (*m_Selected)->m_Value; }

	/*! \fn void AddOption(const std::string& caption, int value)
	*	\brief Add new option to the combobox
	*	\param caption Caption of the option
	*	\param value Value of the option
	*/
	void AddOption(const std::string& caption, int value);
	bool MousePress(int mouseX, int mouseY);
	bool MouseRelease(int mouseX, int mouseY);
	void MouseMove (int x, int y);
	void Draw();

	CComboBox(void);
	~CComboBox(void);
};

}
