#include "StdAfx.h"

#include "GUI.h"
#include "Dialog.h"
#include "Button.h"
#include "Misc.h"

#include <functional>

namespace glgui {

using std::tr1::function;

enum ERetCodes
{
	RET_OK = 0,
	RET_CANCEL,
	RET_YES,
	RET_NO
};

uint32 CDialog::ShowModal ()
{


	CGUI::GetSingleton()->AddControlByPtr(this);
	CGUI::GetSingleton()->SetFocusControl(this);

	return 0;
	// TODO : przemyslec, czy stawiac dialog na drugim watku czy co
	// nie mozna generalnie sie tu zablokowac w ten sposob...

	// Rozwiazanie #1 : wrzucamy go do listy wszystkich kontrolek, 
	// i zapewniamy poprawne usuniêcie poprzez sam dialog.
}

void CDialog::Draw()
{
	if (!(m_DisplayOptions.Visible))
		return;

	glColor3ub(50, 80, 100);
	glBegin (GL_QUADS);
		glVertex2i (m_Position.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y);
		glVertex2i (m_Position.X+m_Size.X, m_Position.Y+m_Size.Y);
		glVertex2i (m_Position.X, m_Position.Y+m_Size.Y);
	glEnd();

	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(m_Position.X, m_Position.Y, 0.f);
	for (auto It = m_Buttons.begin(); It != m_Buttons.end(); It++)
	{
		if ((*It) != 0)
			(*It)->Draw();
	}
	glPopMatrix();
}

bool CDialog::MousePress (int mouseX, int mouseY)
{
	if (_TestIfInside(mouseX, mouseY))
	{
		SetFocus(true);
		// Jesli nastapilo trafienie w obszar dialogu,
		// sprawdzamy trafienia w poszczegolne przyciski
		// TODO: uogolnienie na wszystkie typy kontrolek
		for (auto It = m_Buttons.begin(); It != m_Buttons.end(); It++)
		{
			if ((*It) != 0)
				(*It)->MousePress(mouseX-m_Position.X,mouseY-m_Position.Y);
		}
		return true;
	}
	return false;
}
bool CDialog::MouseRelease (int mouseX, int mouseY)
{
	// Mouserelease musi byæ tak czy siak przekazane do kontrolek
	//if (IsPointInRec<int> (CVector2<int32>(mouseX, mouseY), m_Position, m_Size))
	{
		// Patrz odpowiednia metode MousePress
		for (auto It = m_Buttons.begin(); It != m_Buttons.end(); It++)
		{
			if ((*It) != 0)
				(*It)->MouseRelease(mouseX-m_Position.X,mouseY-m_Position.Y);
		}
		return true;
	}
	//else
		//return false;
}

CDialog::CDialog(void)
{
	for (auto It = m_Buttons.begin(); It != m_Buttons.end(); It++)
	{
		(*It) = 0;
	}

	m_Size.X = 500;
	m_Size.Y = 200;

	m_DisplayOptions.Clicked = false;
	m_DisplayOptions.Enabled = true;
	m_DisplayOptions.Visible = true;

	function<void(void)> TempF = [this](void){ this->m_DisplayOptions.Visible = false; };

	m_Buttons[0] = new CButton();
	m_Buttons[1] = new CButton();

	// OK button
	m_Buttons[0]->SetCaption("OK");
	m_Buttons[0]->SetSize(CVector2<int32>(80, 40));
	m_Buttons[0]->SetPosition (CVector2<int32>(10, 50));
	m_Buttons[0]->SetFunction(TempF);

	// Cancel button
	m_Buttons[1]->SetCaption("Cancel");
	m_Buttons[1]->SetSize(CVector2<int32>(80, 40));
	m_Buttons[1]->SetPosition (CVector2<int32>(100, 50));
	m_Buttons[1]->SetFunction(TempF);
}


CDialog::~CDialog(void)
{
	for (auto It = m_Buttons.begin(); It != m_Buttons.end(); It++)
	{
		// BUG: podwojne usuwanie przy dodawaniu dialogow
		if ((*It) != 0)
		{
			delete (*It);
			(*It) = 0;
		}
		(*It) = 0;
	}
}

}
