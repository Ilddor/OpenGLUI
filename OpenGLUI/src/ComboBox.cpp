#include "StdAfx.h"

#include "ComboBox.h"
#include "Vector2.h"
#include "Misc.h"
#include "Input.h"
#include "GUI.h"

namespace glgui
{
	void CComboBox::_Sort()
	{
		int temp = 0;
		for(auto it = m_List.begin(); it != m_List.end(); ++it)
		{
			if(it != m_Selected)
			{
				++temp;
				(*it)->SetPosition(CVector2<int>(m_Position.X, m_Position.Y+temp*m_Size.Y));
			}
		}
		if(m_IsSelected)
			(*m_Selected)->SetPosition(m_Position);
		m_DropButton.SetPosition(CVector2<int>(m_Position.X+m_Size.X, m_Position.Y));
	}

	void CComboBox::SetPosition(const CVector2<int>& pos)
	{
		m_Position = pos;
		_Sort();
	}

	void CComboBox::SetSize(const CVector2<int>& size)
	{
		m_Size = size;
		/*for(auto it = m_List.begin(); it != m_List.end(); ++it)
		{
			(*it)->SetSize(m_Size);
		}*/
		m_DropButton.SetSize(CVector2<int>(size.Y, size.Y)); //robimy kwadratowy button rozwijania
		_Sort();
	}

	void CComboBox::AddOption(const std::string& caption, int value)
	{
		CComboLabel* temp = new CComboLabel;
		temp->SetSize(m_Size);
		temp->SetCaption(caption);
		temp->m_Value = value;
		m_List.push_back(temp);
		if(m_List.size() == 1 && m_IsSelected == false)
		{
			m_IsSelected = true;
			m_Selected = m_List.begin();
		}
		_Sort();
	}

	bool CComboBox::MousePress(int mouseX, int mouseY)
	{
		if(IsPointInRec(CVector2<int>(mouseX, mouseY), m_Position, m_Size))
		{
			return true;
		}
		if(m_Dropped)
		{
			for(auto it = m_List.begin(); it!=m_List.end(); ++it)
			{
				if((*it)->MousePress(mouseX, mouseY))
				{
					return true;
				}
			}
		}
		if(m_DropButton.MousePress(mouseX, mouseY))
		{
			return true;
		}
		return false;
	}

	bool CComboBox::MouseRelease(int mouseX, int mouseY)
	{
		if(IsPointInRec(CVector2<int>(mouseX, mouseY), m_Position, m_Size))
		{
			if(m_Dropped) m_Dropped = false;
			return true;
		}
		if(m_Dropped)
		{
			for(auto it = m_List.begin(); it!=m_List.end(); ++it)
			{
				if((*it)->MouseRelease(mouseX, mouseY))
				{
					m_Selected = it;
					m_IsSelected = true;
					m_Dropped = false;
					_Sort();
					return true;
				}
			}
		}
		if(m_DropButton.MouseRelease(mouseX, mouseY))
		{
			if(m_Dropped)
				m_Dropped = false;
			else
				m_Dropped = true;
			return true;
		}
		return false;
	}

	void CComboBox::MouseMove(int mouseX, int mouseY)
	{
	}

	void CComboBox::Draw()
	{
		if(m_IsSelected)
			(*m_Selected)->Draw();
		else
			if(!m_List.empty())
				m_List.front()->Draw();
		
		if(m_Dropped)
		{
			for(auto it = m_List.begin(); it != m_List.end(); ++it)
			{
				(*it)->Draw();
			}
		}

		m_DropButton.Draw();
	}

	CComboBox::CComboBox(void)
	{
		m_Dropped = false;
		m_IsSelected = false;
		m_Selected = m_List.end();
		m_DropButton.SetCaption("\\\/");
		m_DropButton.SetFunction(std::tr1::function<void(void)>([this]
		{
			if(m_Dropped)
				m_Dropped = false;
			else
				m_Dropped = true;
		}));
		_Sort();
	}

	CComboBox::~CComboBox(void)
	{
		for(auto it = m_List.begin(); it != m_List.end(); ++it)
		{
			delete (*it);
		}
		m_List.clear();
	}

	//CComboLabel---------------------------------------------------------------------

	bool CComboBox::CComboLabel::MousePress(int mouseX, int mouseY)
	{
		if(IsPointInRec(CVector2<int>(mouseX, mouseY), m_Position, m_Size))
			return true;
		return false;
	}

	bool CComboBox::CComboLabel::MouseRelease(int mouseX, int mouseY)
	{
		if(IsPointInRec(CVector2<int>(mouseX, mouseY), m_Position, m_Size))
			return true;
		return false;
	}

	void CComboBox::CComboLabel::Draw()
	{
		if (!(m_DisplayOptions.Visible))
		return;

		glDisable(GL_TEXTURE_2D);
		glLineWidth (4);

		int X = m_Position.X;
		int Y = m_Position.Y;
		int Width = m_Size.X;
		int Height = m_Size.Y;
	
		// Tlo
		glColor3ub(255, 255, 255);
		glBegin(GL_QUADS);
			glVertex2i (X, Y);
			glVertex2i (X + Width, Y);
			glVertex2i (X + Width, Y + Height);
			glVertex2i (X, Y + Height);
		glEnd();

		//tekst
		glColor3ub(0,0,0);
		CGUI::GetSingleton()->Print(m_Caption.c_str(), m_Position.X,  m_Position.Y);
	}

	//Button z trojkacikiem------------------------------------------

	void CComboBox::CComboButton::Draw()
	{
		if (!(m_DisplayOptions.Visible))
		return;

		glDisable(GL_TEXTURE_2D);
		glLineWidth (4);

		int X = m_Position.X;
		int Y = m_Position.Y;
		int Width = m_Size.X;
		int Height = m_Size.Y;
	
		// Tlo
		glColor3f (0.3f, 0.3f, 0.3f);
		glBegin(GL_QUADS);
			glVertex2i (X, Y);
			glVertex2i (X + Width, Y);
			glVertex2i (X + Width, Y + Height);
			glVertex2i (X, Y + Height);
		glEnd();
	
		// Ramka
		glBegin (GL_LINES);
			if (m_DisplayOptions.Clicked)
				glColor3f (0.1f, 0.1f, .1f);
			else
				glColor3f (0.7f, 0.7f, 0.7f);
			// Gora
			glVertex2i (X, Y);
			glVertex2i (X + Width, Y);
			//Lewo
			glVertex2i (X, Y);
			glVertex2i (X, Y+Height);
		
			if (m_DisplayOptions.Clicked)
				glColor3f (0.7f, 0.7f, 0.7f);
			else
				glColor3f (0.1f, 0.1f, .1f);
			//Prawo
			glVertex2i (X + Width, Y + Height);
			glVertex2i (X, Y + Height);
			//Dol
			glVertex2i (X + Width, Y + Height);
			glVertex2i (X + Width, Y);
		glEnd();
	
		glColor3ub(0,0,0);

		glBegin(GL_POLYGON);
			glVertex2i (X+0.2*Width, Y+0.2*Height);
			glVertex2i (X+0.8*Width, Y+0.2*Height);
			glVertex2i (X+0.5*Width, Y+0.8*Height);
		glEnd();
	}
}
