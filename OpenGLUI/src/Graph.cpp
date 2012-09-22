#include "stdafx.h"
#include "Graph.h"

namespace glgui {

using namespace std;

void CGraph::Draw()
{
	glDisable (GL_TEXTURE_2D);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	// Przesuwamy sie na dol, bo rysujemy do gory (wyzej - wieksze y)
	glTranslatef(m_Position.X, m_Position.Y + m_Size.Y, 0.f);
	unsigned int DataSize = m_Data.size();
	if (DataSize == 0)
		return;

	int DrawingCount = (m_StepX != 0) ? (m_Size.X / m_StepX) : (m_Size.X / DataSize);
	if (DrawingCount >= DataSize)
		DrawingCount = DataSize - 1;

	double Density = m_Bounds.Y - m_Bounds.X;

	// Rysujemy t³o
	glColor4ub (0, 0, 0, 128);
	//TODO DrawRect(0, 0, m_Size.X, -m_Size.Y);

	glColor4ub (255, 0, 0, 192);
	switch (m_DrawType)
	{
	case EDrawType::LINES:
		glBegin (GL_LINE_STRIP);
		for (unsigned int i = 0; i < DrawingCount; ++i)
		{
			// Rysujemy ostatie probki z danych
			// Minus, bo rysujemy do góry
			double Y = -(m_Data[i+DataSize-DrawingCount] + m_Bounds.Y) / Density * m_Size.Y + m_Size.Y;
			glVertex2d(i * m_StepX, Y);
		}
		glEnd();
		break;

	case EDrawType::POINTS:
		glPointSize(5.0f);
		glBegin (GL_POINTS);
		for (unsigned int i = 0; i < DrawingCount; ++i)
		{
			double Y = (m_Data[i]+m_Bounds.Y) / Density * m_Size.Y;
			glVertex2d(i * m_StepX, Y);
		}
		glEnd();
		break;

	case EDrawType::RECTANGLES:
		break;
	}
	glPopMatrix();
}

void CGraph::AddData (const double data)
{
	m_Data.push_back(data);
}
void CGraph::AddData (const vector<double>& data)
{
	m_Data.insert (m_Data.end(), data.begin(), data.end());
}
void CGraph::AddData (const double* data, unsigned int size)
{
	m_Data.insert (m_Data.end(), data, data+size*sizeof(double));
}

CGraph::CGraph()
{
	m_DrawType = EDrawType::LINES;
	m_Size.X = m_Size.Y = 512.f;
}


CGraph::~CGraph(void)
{
}

}
