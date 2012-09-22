#pragma once
#include "Singleton.h"
#include <string>

namespace glgui {

/*! \class CXmlLoader
* \brief XmlLoader class
*
*	This class is used to load buttons from Xml file
*/
class CXmlLoader :
	public CSingleton<CXmlLoader>
{

public:
	/*! \fn void LoadFile(const std::string& path)
	*	\brief Load buttons from Xml file
	*	\param path Path of the Xml file to load
	*/
	void LoadFile (const std::string& path);

	CXmlLoader(void);		//!< \public Default constructor
	~CXmlLoader(void);		//!< \public Default destructor
};

}
