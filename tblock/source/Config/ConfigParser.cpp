#include "PlatformPrecomp.h"
#include "ConfigParser.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

ConfigParser::ConfigParser( std::string name, std::string parentDebugInfo )
{
	debugInfo = parentDebugInfo + ", " + name;
}

ConfigParser::ConfigParser( std::string configFile, char** envp )
{
	parseFailed = false;

	debugInfo = configFile;
	groupStack.push_front( this );

	FILE* in = fopen( configFile.c_str(), "r" );
	if( !in )
	{
		parseFailed = true;
	}

	char buff[1024];
	while( fgets( buff, 1024, in ) )
	{
		std::string line = buff;
		if( ( line.length() > 2) && ( line[0] != '#' ) && ( line.find(')') == std::string::npos ) )
		{
			std::string name;
			std::string value;
			split( line, name, value, '=' );

			if( value == "(" )
			{
				ConfigParser* newGroup = new ConfigParser( name, debugInfo );
				groupStack.front()->groups[name] = newGroup;
				groupStack.push_front( newGroup );
			}
			else
			{
				for( std::list<ConfigParser*>::reverse_iterator i = groupStack.rbegin(); i != groupStack.rend(); ++i )
				{
					(*i)->symbolExpand( value );
				}
				envSymbolExpand( value );
				groupStack.front()->add( name, value );
			}
		}

		if( ( line.length() > 0 ) && ( line[0] != '#' ) && ( line.find( ')' ) != std::string::npos ) )
		{
			groupStack.pop_front();
		}
	}

	fclose( in );
}

ConfigParser::~ConfigParser()
{
	for( std::map<std::string, ConfigParser*>::iterator i = groups.begin(); i != groups.end(); ++i )
	{
		delete i->second;
	}
}

void ConfigParser::add( std::string name, std::string value )
{
	symbols[name] = value;
}

void ConfigParser::split( std::string in, std::string& left, std::string& right, char c )
{
	size_t pos = in.find_first_of( c );
	
	if( pos == std::string::npos )
	{
		left = in;
		trim( left );
		right = "";
	}
	else if( pos <= 1 )
	{
		left = "";
		right = in.substr( pos+1, std::string::npos );
		trim( right );
	}
	else
	{
		left = in.substr( 0, pos - 1 );
		trim( left );
		right = in.substr( pos + 1, std::string::npos );
		trim( right );
	}
}

void ConfigParser::trim( std::string& s )
{
	while( ( s.length() > 1 ) && ( (s[0] == ' ' ) || ( s[0] =='\t' ) ) )
	{
		s = s.substr( 1, std::string::npos );
	}

	while( ( s.length() > 1 ) &&
			( ( s[s.length()-1] == ' ' ) ||
			  ( s[s.length()-1] == '\t' ) || 
			  ( s[s.length()-1] == '\n' ) || 
			  ( s[s.length()-1] == '\r' ) ) )
	{
		s = s.substr( 0, s.length() - 1 );
	}

	if( ( s.length() > 1 ) && ( s[0] == '"' ) )
	{
		s = s.substr( 1, string::npos );
	}

	if( ( s.length() > 1 ) && ( s[s.length() - 1 ] == '"' ) )
	{
		s = s.substr( 0, s.length() - 1 );
	}
}

void ConfigParser::symbolExpand( std::string& s )
{
	symbolExpand( symbols, s );
}

void ConfigParser::envSymbolExpand( std::string& s )
{
	symbolExpand( envSymbols, s );
}

void ConfigParser::symbolExpand( std::map<std::string, std::string>& symbols, std::string& s )
{
	bool expanded;
	do
	{
		expanded = false;
		for( std::map<std::string, std::string>::iterator i = symbols.begin(); i != symbols.end(); ++i )
		{
			std::string search = "%" + i->first + "%";
			std::string replace = i->second;
			size_t pos = s.find( search );
			if( pos != std::string::npos )
			{
				expanded = true;
				s.replace( pos, search.length(), replace );
			}
		}
	}
	while( expanded );
}

std::string ConfigParser::pString(std::string name)
{
	std::map<std::string, std::string>::iterator i = symbols.find( name );
	if( i == symbols.end() )
	{
		parseFailed = true;
	}
	return i->second;
}

bool ConfigParser::pBool( std::string name )
{
	std::string val = pString( name );

	if ( ( val == "yes" ) ||
	     ( val == "Yes" ) ||
	     ( val == "YES" ) ||
		 ( val == "true" ) ||
	     ( val == "True" ) ||
	     ( val == "TRUE" ) )
	{
		return true;
	}

	return false;
}

double ConfigParser::pDouble( std::string name )
{
	std::string val = pString( name );

	return atof( val.c_str() );
}

int ConfigParser::pInt( std::string name )
{
	std::string val = pString( name );

	return atoi( val.c_str() );
}

bool ConfigParser::isParsed()
{
	return !parseFailed;
}