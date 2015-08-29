#ifndef _EXMLMENYTYPES_H_
#define _EXMLMENYTYPES_H_

enum E_XML_MENU_TYPE
{
	EXMT_IMAGEVIEW = 0,
	EXMT_LABEL	   = 1,
	EXMT_DIALOG	   = 2,
	EXMT_CHECKBOX  = 3,

	EXMT_COUNT,
	EXMT_NONE
};

enum E_XML_MENU_CLASS
{
	EXMC_BACKGROUND  = 0,
	EXMC_IMAGE		 = 1,
	EXMC_IMAGEBUTTON = 2,
	EXMC_TEXT		 = 3,
	EXMC_TEXTBUTTON  = 4,
	EXMC_CHECKBOX	 = 5,

	EXMC_COUNT,
	EXMC_NONE
};

static std::string XML_MENU_TYPE_STR[] =
{
	"imageview",
	"label",
	"dialog",
	"checkbox"
};

static std::string XML_MENU_CLASS_STR[] =
{
	"background",
	"image",
	"imagebutton",
	"text",
	"textbutton",
	"checkbox"
};

static E_XML_MENU_CLASS convertClassNameToID( const char* className )
{
	unsigned short int i;
	for( i = 0; i < EXMC_COUNT; ++i )
	{
		if( strcmp( className, XML_MENU_CLASS_STR[i].c_str() ) == NULL )
		{
			E_XML_MENU_CLASS classId;
			classId = static_cast< E_XML_MENU_CLASS >( i );
			return classId;
		}
	}

	return EXMC_NONE;
}

#endif