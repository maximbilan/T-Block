#include "PlatformPrecomp.h"
#include "Config.h"
#include <stdio.h>
#include <stdlib.h>
#include "ConfigParser.h"
#include <algorithm>

void Config::Init()
{
	langpack = new LangPack();
}

void Config::Remove()
{
	scores.clear();
	delete (LangPack*) langpack;
}

void Config::Load()
{
	ConfigParser config( GetSavePath() + CONFIG_FILENAME, NULL );

	music = config.pBool( "music" );
	soundEffects = config.pBool( "soundEffects" );
	accelerometer = config.pBool( "accelerometer" );
	vibration = config.pBool( "vibration" );
	startLevel = config.pInt( "startLevel" );
	lang = (E_LANG_TYPE)config.pInt( "language" );

	// get properties for all subgroups starting with prefix
	scores.clear();
	std::map<string, ConfigParser*> messages = config.getGroups();	// all groups
	const string messagePrefix = "Score";	// prefix for group name
	for( std::map<string, ConfigParser*>::iterator i = messages.begin(); i != messages.end(); ++i )
	{
		string groupName = i->first;
		ConfigParser* group = i->second;

		// test group name for prefix
		if( groupName.substr( 0, messagePrefix.length() ) == messagePrefix )
		{
			// display group contents
			scores.insert( scores.begin(), std::pair<long int,std::string>( group->pInt( "value" ), group->pString( "name" ) ) );
		}
	}

	ReloadLang( LANG_ID );
	ReloadLang( lang );
}

void Config::Save()
{
	std::string path = GetSavePath() + CONFIG_FILENAME;
	FILE* fp = fopen( path.c_str(), "w" );

	if( !fp )
	{
		LogMsg( "can not create file %s", path.c_str() );
		return;
	}

	fputs( "# mTetris Config File\n\n", fp );

	fputs( "soundEffects = ", fp );
	if( soundEffects )
	{
		fputs( "true", fp );
	}
	else
	{
		fputs( "false", fp );
	}
	fputs( "\n\n", fp );

	fputs( "music = ", fp );
	if( music )
	{
		fputs( "true", fp );
	}
	else
	{
		fputs( "false", fp );
	}
	fputs( "\n\n", fp );

	fputs( "accelerometer = ", fp );
	if( accelerometer )
	{
		fputs( "true", fp );
	}
	else
	{
		fputs( "false", fp );
	}
	fputs( "\n\n", fp );

	fputs( "vibration = ", fp );
	if( vibration )
	{
		fputs( "true", fp );
	}
	else
	{
		fputs( "false", fp );
	}
	fputs( "\n\n", fp );

	fputs( "startLevel = ", fp );
	char stringStartLevel[12] = {0};
	sprintf( stringStartLevel, "%d", startLevel );
	fputs( stringStartLevel, fp );
	fputs( "\n\n", fp );

	fputs( "language = ", fp );
	char stringLang[12] = {0};
	sprintf( stringLang, "%d", lang );
	fputs( stringLang, fp );
	fputs( "\n\n", fp );

	short int i = 0;
	for( scores_t::iterator ii=scores.begin(); ii != scores.end(); ii++ )
	{
		i++;
		char str[10];
		sprintf( str, "Score %ld", i );
		fputs( str, fp );

		fputs( " = (\n", fp );
		fputs( "\t name = ", fp );
		fputs( ii->second.c_str(), fp );
		fputs( "\n", fp );
		fputs( "\t value = ", fp );
		sprintf( str, "%ld",ii->first );
		fputs( str, fp );
		fputs( "\n)\n\n", fp );
	}

	fputs( "\n", fp );

	fclose( fp );
}

void Config::ResetToDefault()
{
	music = true;
	soundEffects = true;
	accelerometer = true;
	vibration = false;
	startLevel = 1;
	lang = LANG_EN;
	
	ReloadLang( LANG_ID );
	ReloadLang( lang );
	
	// Test scores
	//addNewScore("asdf1",4342798);
	//addNewScore("asdf1",4342);
	//addNewScore("asdf3",35);
	//addNewScore("asdf4",4342);
	//addNewScore("asdf5",45);
	//addNewScore("asdf6",4342);
	//addNewScore("asdf7",45);
	//addNewScore("asdf8",4342);
	//addNewScore("asdf9",45);
	//addNewScore("asdf10",4342);
	//addNewScore("asdf11",45);
	//addNewScore("asdf12",4342);
	//addNewScore("asdf13",45);
	//addNewScore("asdf10",4342);
	//addNewScore("asdf11",45);
	//addNewScore("asdf12",4342);
	//addNewScore("asdf13",45);
}

void Config::addNewScore( const std::string name, const long int value )
{
	scores.insert(scores.begin(), std::pair<long int,std::string>( value, name ) );

	if( scores.size() > SCORES_CNT )
	{
		int cnt = 0;
		for( std::multimap<long int,std::string,greater<long int> >::iterator it = scores.begin(); it!= scores.end(); ++it )
		{
			cnt++;
			if( cnt > SCORES_CNT )
			{
				// it doesn't work on android
				scores.erase( it, scores.end() );
				break;
			}
		}
	}
}

long int Config::getMinScore()
{
	long int result;
	if( scores.size() == 0 )
	{
		return 0;
	}

	for( scores_t::const_iterator it = scores.begin(); it != scores.end(); ++it )
	{
		result = (*it).first;
	}

	return result;
}