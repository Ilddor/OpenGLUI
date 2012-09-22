#include "stdafx.h"
#include "DebugView.h"
#include "Vector2.h"
#include "Button.h"
#include "Label.h"
#include "GUI.h"
#include <boost/lexical_cast.hpp>
#include <string>
#include <functional>

using namespace std;
using boost::lexical_cast;

namespace glgui {

void CDebugView::CElement::Draw(const CVector2<int>& position)
{
	CVector2<int> Pos = position;
	m_Label->SetCaption(m_Name);
	m_Label->SetPosition(Pos);
	//m_Label->SetFontSize(20);
	m_Label->Draw();
	
	Pos.X += 100;
	//m_Label->SetCaption(string (": ")+lexical_cast<string,float>((*m_ValuePtr)));
	m_Label->SetPosition(Pos);
	m_Label->Draw();

	Pos.X += 140;
	m_ButtonAdd->SetPosition(Pos);
	m_ButtonAdd->Draw();

	Pos.X += 20;
	m_ButtonSub->SetPosition(Pos);
	m_ButtonSub->Draw();
}

CDebugView::CElement::CElement()
{
	m_ButtonAdd = new CButton();
	m_ButtonSub = new CButton();
	m_Label = new CLabel();

	tr1::function<void(void)> TempFunc;
	{
		m_ButtonAdd->SetSize(CVector2<int>(20,20));
		m_ButtonAdd->SetCaption("+");
		//TempFunc = [&](){ (*m_ValuePtr) += 1.0f; };
		m_ButtonAdd->SetFunction(TempFunc);
	}
	{
		m_ButtonSub->SetSize(CVector2<int>(20,20));
		m_ButtonSub->SetCaption("-");
		//TempFunc = [&](){ (*m_ValuePtr) += 1.0f; };
		m_ButtonSub->SetFunction(TempFunc);
	}
}

CDebugView::CElement::~CElement()
{
	delete m_ButtonAdd;
	delete m_ButtonSub;
	delete m_Label;
}

void CDebugView::SetField (const std::string& ident, const float& val)
{
	/*if (m_Fields.find(ident) != m_Fields.end())
		(*m_Fields[ident]) = val;
	else
	{
		float& Val = const_cast<float&>(val);
		//CElement* Temp = new CElement;
		//Temp->SetName(ident);
		//Temp->SetValuePtr (&Val);
		//m_Fields.insert(make_pair<string, CElement*>(ident, Temp));
	}*/
}

void CDebugView::SetStatic (const std::string& ident, float val)
{
	m_Statics[ident] = val;
}

void CDebugView::Draw (void)
{	
	int Counter = 0;

	for (auto It = m_Fields.begin(); It !=m_Fields.end(); It++)
	{
		It->second->Draw(CVector2<int>(10, Counter*20));
		Counter++;
	}
	for (auto It = m_Statics.begin(); It != m_Statics.end(); It++)
	{
		CGUI::GetSingleton()->Print(It->first+lexical_cast<string,float>(It->second), 10, Counter*20);
		Counter++;
	}
}
//-----------------------------------------------------------------------------------------------
bool CDebugView::MousePress (int mouseX, int mouseY)
{
	return false;
}
bool CDebugView::MouseRelease (int mouseX, int mouseY)
{
	return false;
}
//-----------------------------------------------------------------------------------------------
/*
void CGUI::SetDebugField (const string& ident, const string& val)
{
	m_DebugFields[ident] = PrepareForPrint(val);
}
void CGUI::SetDebugField (const string& ident, const float val)
{
	m_DebugFields[ident] = PrepareForPrint(lexical_cast<string>(val));
}
void CGUI::SetDebugField (const string& ident, const int val)
{
	m_DebugFields[ident] = PrepareForPrint(lexical_cast<string>(val));
}*/

CDebugView::CDebugView(void)
{
}


CDebugView::~CDebugView(void)
{
	for (auto It = m_Fields.begin(); It !=m_Fields.end(); It++)
	{
		delete It->second;
	}
}

}