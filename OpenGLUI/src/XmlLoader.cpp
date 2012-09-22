#include "stdafx.h"
#include "XmlLoader.h"
#include "GUI.h"
#include "Typedefs.h"
#include <rapidxml.hpp>
#include <map>

#include "Button.h"
#include "Frame.h"
#include "Slider.h"

namespace glgui {

std::map<std::string, std::tr1::function<CControl*(rapidxml::xml_node<>*)>> LoadFunctions;
std::map<std::string, std::tr1::function<CFrame*()>> AddedControls;

char *TextFileRead(const char *fn) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) 
	{
		fp = fopen(fn,"rt");

		if (fp != NULL) 
		{
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);

			if (count > 0) 
			{
				content = (char *)malloc(sizeof(char) * (count+1));
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}

// TODO: jakoœ to zebraæ do kupy

CVector2<int32> NodeToVector2 (rapidxml::xml_node<>* node)
{
	CVector2<int> TempV;
	TempV.X = atof(node->first_attribute("x")->value());
	TempV.Y = atof(node->first_attribute("y")->value());
	return TempV;
}

CControl* LoadControl (rapidxml::xml_node<>* node);

CButton* LoadButton (rapidxml::xml_node<>* Node)
{
	CButton* CtrlPtr = new CButton;
	{ // Pozycja
		auto Position = Node->first_node("position");
		if (Position != 0)
			CtrlPtr->SetPosition(NodeToVector2(Position));
	}
	{ // Rozmiar
		auto Size = Node->first_node("size");
		if (Size != 0)
			CtrlPtr->SetSize(NodeToVector2(Size));
	}
	{ // Caption
		auto Caption = Node->first_node("caption");
		if (Caption != 0)
			CtrlPtr->SetCaption(Caption->value());
	}
	return CtrlPtr;
}

CFrame* LoadFrame (rapidxml::xml_node<>* Node)
{
	CFrame* CtrlPtr = new CFrame;
	{ // Pozycja
		auto Position = Node->first_node("position");
		if (Position != 0)
			CtrlPtr->SetPosition(NodeToVector2(Position));
	}
	{ // Rozmiar
		auto Size = Node->first_node("size");
		if (Size != 0)
			CtrlPtr->SetSize(NodeToVector2(Size));
	}
	for (auto Sub = Node->first_node("controls")->first_node(); Sub != 0; Sub = Sub->next_sibling())
	{
		CtrlPtr->AddControlByPtr(LoadControl(Sub));
	}
	return CtrlPtr;
}

CSlider* LoadSlider (rapidxml::xml_node<>* Node)
{
	CSlider* CtrlPtr = new CSlider;
	{ // Pozycja
		auto Position = Node->first_node("position");
		if (Position != 0)
			CtrlPtr->SetPosition(NodeToVector2(Position));
	}
	{ // Rozmiar
		auto Size = Node->first_node("size");
		if (Size != 0)
			CtrlPtr->SetSize(NodeToVector2(Size));
	}
	{ //Horizontal
		auto Horizontal = Node->first_node("horizontal");
		if(Horizontal != 0)
			CtrlPtr->SetHorizontal(Horizontal->value());
		else
			CtrlPtr->SetHorizontal(true);
	}
	{ //Inne
		auto Properties = Node->first_node("properties");
		if(Properties != 0)
		{
			if(Properties->first_attribute("max") != 0)
				CtrlPtr->RangeMax = atoi(Properties->first_attribute("max")->value());
			else
				CtrlPtr->RangeMax = 100;
			if(Properties->first_attribute("min") != 0)
				CtrlPtr->RangeMin = atoi(Properties->first_attribute("min")->value());
			else
				CtrlPtr->RangeMin = 0;
			if(Properties->first_attribute("value") != 0)
				CtrlPtr->Value = atoi(Properties->first_attribute("value")->value());
			else
				CtrlPtr->Value = 1;
		}
		else
		{
			CtrlPtr->RangeMin = 0;
			CtrlPtr->RangeMax = 100;
			CtrlPtr->Value = 1;
		}
	}
	return CtrlPtr;
}

CControl* LoadControl (rapidxml::xml_node<>* node)
{
	const char* Type = node->name();
	/*if (!strcmp(Type, "button")) // 0 means equal
		return LoadButton(node);
	else if (!strcmp(Type, "frame"))
		return LoadFrame (node);
	else
		return 0;*/		//mozna wywaliæ
	auto it = LoadFunctions.find(Type);
	if(it != LoadFunctions.end())
		return it->second(node);
	else
		return 0;
}

void CreateControl (rapidxml::xml_node<>* node)
{
	std::string Name = (node->first_attribute("name"))->value();
	if(!strcmp((node->first_attribute("extends"))->value(), "frame"))
	{
		AddedControls.insert(std::make_pair(Name, [=]()->CFrame*
		{
			CFrame* CtrlPtr = new CFrame;
			CtrlPtr->SetSize(NodeToVector2(node->first_node("size")));
			for(auto Sub = node->first_node("controls")->first_node(); Sub != 0; Sub = Sub->next_sibling())
			{
				CtrlPtr->AddControlByPtr(LoadControl(Sub));
			}
			return CtrlPtr;
		}));

		LoadFunctions.insert(std::make_pair(Name, [](rapidxml::xml_node<>* Node)->CControl*
		{
			CFrame* CtrlPtr = AddedControls.find(Node->name())->second();
			if(CtrlPtr)
			{ // Pozycja
				auto Position = Node->first_node("position");
				if (Position != 0)
					CtrlPtr->SetPosition(NodeToVector2(Position));
			}
			else
			{
				delete CtrlPtr;
				CtrlPtr = 0;
			}
			return CtrlPtr;
		}));
	}
}

void CXmlLoader::LoadFile(const std::string& path)
{
	//TODO: przerobic te funkcje odrazu w insercie zeby nie bylo tak okropnie
	LoadFunctions.insert(std::make_pair("button", *LoadButton));
	LoadFunctions.insert(std::make_pair("frame", *LoadFrame));
	LoadFunctions.insert(std::make_pair("slider", *LoadSlider));

	rapidxml::xml_document<> Doc;
	char* FileData = TextFileRead(path.c_str());

	Doc.parse<0>(FileData);
	auto Root = Doc.first_node();
	for (auto Node = Root->first_node(); Node != 0; Node = Node->next_sibling())
	{
		if(!strcmp(Node->name(), "class"))
		{
			CreateControl(Node);
		}
		else
		{
			CControl* Temp = LoadControl(Node);
			if (Temp)
				CGUI::GetSingleton()->AddControlByPtr(Temp);
		}
	}
}

CXmlLoader::CXmlLoader(void)
{
}


CXmlLoader::~CXmlLoader(void)
{
}

}