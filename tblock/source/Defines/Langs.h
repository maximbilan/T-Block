#ifndef _C_LANGS_H_
#define _C_LANGS_H_

enum E_LANG_TYPE
{
	LANG_EN,
	LANG_RU,

	LANG_ID,
	LANG_COUNT
	
};

static char* LANG_NAMES[] =
{
	"EN",
	"RU",
	"ID"
};

static char* LANG_NAMES_STR[] =
{
	"English",
	"Русский",
	"ID"
};

#define DEFAULT_LANG_TYPE LANG_EN

static E_LANG_TYPE convertCodeToId( char* langCode )
{
	if( langCode == "EN" )
	{
		return LANG_EN;
	}
	if( langCode == "RU" )
	{
		return LANG_RU;
	}
	if( langCode = "ID" )
	{
		return LANG_ID;
	}

	return DEFAULT_LANG_TYPE;
};

#endif