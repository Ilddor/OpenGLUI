#pragma once
#include "Control.h"
#include "Vector2.h"
#include <map>

namespace glgui {

class CButton;
class CLabel;

class CDebugView :
	public CControl
{
	class CElement
	{
	protected:
		bool		m_IsConst;
		std::string	m_Name;
		CButton*	m_ButtonAdd;
		CButton*	m_ButtonSub;
		CLabel*		m_Label;

		CElement ();
	public:
		virtual inline void SetName (const std::string& name) { m_Name = name; }
		virtual void Draw (const CVector2<int>& position);
		virtual ~CElement ();

	private: // non-copyable
		CElement& operator= (const CElement& other);
		CElement (const CElement& other);
	};

	class CStaticElement : public CElement
	{
	protected:
		float m_Value;
	};

	class CDynamicElement : public CElement
	{
	protected:
		float*		m_ValuePtr;

	public:
		void Draw (const CVector2<int>& position);
		void operator= (float value) { (*m_ValuePtr) = value; }
		void SetPtr (float* valPtr) { m_ValuePtr = valPtr; }
		
		CDynamicElement ();
		~CDynamicElement (void);
	};

protected:
	std::map<std::string, CElement*>	m_Fields;
	std::map<std::string, float>	 m_Statics;

public:
	void SetField (const std::string& ident, const float& val);
	void SetStatic (const std::string& ident, float val);
	void Draw ();
	bool MousePress (int mouseX, int mouseY);
	bool MouseRelease (int mouseX, int mouseY);
	void MouseMove (int mouseX, int mouseY) { }
	void KeyPress (char key) { }

	CDebugView(void);
	~CDebugView(void);
};

}
