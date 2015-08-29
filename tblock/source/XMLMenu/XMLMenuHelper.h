#ifndef _XMLMenuHELPER_H_
#define _XMLMenuHELPER_H_

#include <string>

enum E_XMLMENU_ALIGNMENT
{
	XMLMENU_ALIGNMENT_UPPER_LEFT,
	XMLMENU_ALIGNMENT_CENTER,
	XMLMENU_ALIGNMENT_DOWN_CENTER,
	XMLMENU_ALIGNMENT_UPPER_RIGHT,
	XMLMENU_ALIGNMENT_DOWN_LEFT,
	XMLMENU_ALIGNMENT_UPPER_CENTER,
	XMLMENU_ALIGNMENT_LEFT_CENTER,

	XMLMENU_COUNT
};

static char* XMLMenuAlignemntStr[] =
{
	"upper_left",
	"center",
	"down_center",
	"upper_right",
	"down_left",
	"upper_center",
	"left_center"
};


class XMLMenuHelper
{
	public:
		static bool charToBool( char* value )
		{
			//if( strcmp( strupr( value ), "TRUE" ) == NULL )
			if( strcmp( value, "true" ) == 0 )
			{
				return true;
			}
			else	
			{
				return false;
			}
		};

		static int convertAlignmentStrToInt( const char* value )
		{
			int i;
			for( i = 0; i < XMLMENU_COUNT; ++i )
			{
				if( !strcmp( value, XMLMenuAlignemntStr[i] )  )
				{
					return i;
				}
			}

			return 0;
		};
};

#endif