#include "stdafx.h"
#include "Misc.h"
#include <cmath>
#include <cstdlib>
#include <string>

namespace glgui {

using namespace std;
#pragma warning(disable: 4244)
//---------------------------------------------
inline int Rnd (float f)
{
	return int(f+0.5); // Szybsze 
}
//---------------------------------------------
inline float DotPart (float f)
{
	 return f-int(f); // Mniej pamieci zajmuje
}
//---------------------------------------------
inline float Average (float a, float b)
{
   return (a+b) / 2;
}          

//---------------------------------------------
int Random (int range_min, int range_max)
{
	return (rand()%(range_max-range_min))+range_min;
	// Powiedz mi potem po co takie komplikacje, zamieniam na krotsze i szybsze
	/*
	  float u = (double)rand() / (RAND_MAX + 1) * (range_max - range_min)
			+ range_min;
//int u = (int)(((rand() / RAND_MAX) * (max - min)) + min);
	return Rnd(u);
	*/
}

//---------------------------------------------------------------------------------------
float odl_od1_do2 (float X1, float Y1, float X2, float Y2)
{	
	return (sqrt ( Sqre(abs (X1-X2)) 
				 + Sqre(abs (Y1-Y2)) ));
}
//---------------------------------------------
float kat_od1_do2 (float X1, float Y1, float X2, float Y2)
{   
	float l;

	if (X1 == X2)
	{
	 if (Y2 < Y1)
		 return 0.0f;     
	 else
		 return 180.0f;
	}

	if (Y1 == Y2)
	{
	 if (X2 < X1)
		 return 270.0f;     
	 else
		 return 90.0f;
	}

	l = atan2f ( (Y2-Y1), (X2-X1) );
	l *= RAD_TO_DEGREE;
	l += 90;
	if (l<0) l += 360.0f;
		   
	return l;
}       
//================================================================
string ToLower (const string& in)
{
	string Temp;
	for (string::const_iterator It = in.begin(); It != in.end(); It++)
	{
		const char TempC = *It;
		if (TempC >= 'A' && TempC <= 'Z')
			Temp += (char)(TempC) + 'a'-'A';
		else
			Temp += (char)(TempC);
	}
	return Temp;
}

}

