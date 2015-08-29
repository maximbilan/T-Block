#include "PlatformPrecomp.h"
#include "Resource.h"

Resource::Resource()
{
}

Resource::~Resource()
{
}

std::string Resource::getItem( E_RESOLUTION_TYPE rt_type, E_RES_TYPE res_type, E_RES_ID res_id )
{	
	char string[1024] = "";
	strcat(string, RES_TYPE_ARRAY[res_type]);
	strcat(string, "/");

	if( res_type == RES_TYPE_INTERFACE )
	{
		strcat( string, "atlases/" );
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
		strcat( string, RES_ID_ARRAY[res_id] );
		strcat( string, ".rttex" );
	}

	if( res_type == RES_TYPE_AUDIO )
	{
		strcat( string, RES_ID_ARRAY[res_id] );
		strcat( string, ".wav" );
	}

	if( res_type == RES_TYPE_FONT )
	{
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
		strcat(string, RES_ID_ARRAY[res_id] );
		strcat(string, ".rtfont");
	}

	if( res_type == RES_TYPE_GAME )
	{
		strcat( string, "img/" );
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
		strcat( string, RES_ID_ARRAY[res_id] );
		strcat( string, "_" );
		//rt_type = RT_320_480;
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, ".rttex" );
	}

	if( res_type == RES_TYPE_MENU )
	{
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
	}

	if( res_type == RES_TYPE_SPRITE )
	{
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
	}

	if( res_type == RES_TYPE_ATLAS )
	{
		strcat( string, RESOLUTION_TYPE_STR[rt_type] );
		strcat( string, "/" );
	}

	return string;
}