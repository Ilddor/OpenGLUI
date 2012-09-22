#pragma once
#include "Typedefs.h"
#include "Control.h"
#include <vector>
#include "Sizeable.h"

namespace glgui {

/*! \class CGraph
* \brief Graph class
*
*	Class used to create graph
*/
class CGraph :
	public CControl,
	public CSizeable
{
protected:
	std::vector<double>	m_Data;		//!< \protected Stored data
	CVector2<float64>	m_Bounds;	//!< \protected Bounds of graph
	uint32				m_StepX;	//!< \protected Step of graph

	/*! \enum DrawType enum
	*/
	enum EDrawType 
	{
		POINTS,		//!< POINTS
		LINES,		//!< LINES
		RECTANGLES	//!< RECTANGLES
	} m_DrawType;					//!< \protected Draw type

public:
	void Draw ();
	/*! \fn void AddData(const double data)
	*	\brief Add data by single value
	*	\param data Data value
	*/
	void AddData (const double data);

	/*! \fn void AddData(const std::vector<double>& data)
	*	\brief Add data by complete vector of data
	*	\param data Reference to vector
	*/
	void AddData (const std::vector<double>& data);

	/*! \fn void AddData(const double* data, unsigned int size)
	*	\brief Add data by array
	*	\param data Pointer to first cell
	*	\param size Number of elements in array
	*/
	void AddData (const double* data, unsigned int size);

	/*! \fn void Clear()
	*	\brief Clear data in graph
	*/
	void Clear () { m_Data.clear(); }
	// 0 oznacza skalowanie na ca³y ekran

	/*! \fn void SetXStep(uint32 step = 0)
	*	\brief Set step of the graph
	*	\param step Step of graph in pixels
	*/
	void SetXStep (uint32 step = 0) { m_StepX = step; }

	/*! \fn void SetBounds(const CVector2<double>& bounds)
	*	\brief Set bounds of graph
	*	\param bounds Reference of vector
	*/
	void SetBounds (const CVector2<double>& bounds) { m_Bounds = bounds; }

	CGraph(void);
	~CGraph(void);
};

}

