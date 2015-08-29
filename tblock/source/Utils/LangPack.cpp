#include "PlatformPrecomp.h"
#include "LangPack.h"
#include <iostream>
#include <fstream>
#include "Defines/Langs.h"
#include "FileSystem/StreamingInstance.h"

LangPack::LangPack()
{
}

LangPack::~LangPack()
{
	m_strings.clear();
}

void LangPack::ReadPack( unsigned short int lang )
{
	LogMsg("Read Language - starting...");

	char filename[16] = "";
	char* ext = ".lang";
	char* folder = "langs/";

	strcat( filename, LANG_NAMES[lang] );
	strcat( filename, ext );
	
	if( lang == LANG_ID )
	{
		m_ids.clear();
	}
	else
	{
		m_strings.clear();
	}
	
	FileInstance file( folder + std::string( filename ) );
	LogMsg( "I just loaded a file into memory that is %d bytes.", file.GetSize() );
	char temp[4096] = "";
	strcat( temp, file.GetAsChars() );

	const char* buf = file.GetAsChars();

	char * pch;
	pch = strtok( temp,"\n" );
	unsigned int index = 0;
	while( pch != NULL )
	{
		if( lang == LANG_ID )
		{
			m_ids.insert( std::pair< std::string, unsigned int >( std::string( pch ), index ) );
			index++;
		}
		else
		{
			m_strings.push_back( std::string( pch ) );
		}
		pch = strtok( NULL, "\n" );
	}

	LogMsg( "Read language - finishing..." );
}

std::string LangPack::GetString( unsigned short int id )
{
	return m_strings[id];
}

std::string LangPack::GetString( const char* textID )
{
	unsigned short int id = 0;

	std::map<std::string, unsigned int>::iterator findIt;

	findIt = m_ids.find( textID );

	if( findIt != m_ids.end() )
	{
		id = findIt->second;
	}
	else
	{
		return std::string( "" );
	}

	return m_strings[id];
}