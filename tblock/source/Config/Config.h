#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "Interface/Singleton.h"
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include "Defines/Langs.h"
#include "Utils/LangPack.h"

#define CONFIG_FILENAME "Config.cfg"
#define SCORES_CNT 10

typedef std::multimap<long int,std::string,greater<long int> > scores_t;

class Config : public Singleton<Config>
{
	protected:
		Config(){}
	
		friend class Singleton<Config>;

		bool soundEffects;
		bool music;
		bool accelerometer;
		bool vibration;

		unsigned short int startLevel;

		// Map for scores
		scores_t scores;

		E_LANG_TYPE lang;
		LangPack *langpack;

	public:

		void Load();			// Load configurations from file Config.cfg
		void Save();			// Save configurations to file Config.cfg
		void ResetToDefault(); // Reset configurations

		void Init();
		void Remove();

		// Methods for setting parameters
		void setSoundEffects( const bool value );
		void setMusic( const bool value );
		void setAccelerometer( const bool value );
		void setVibration( const bool value );
		void setStartLevel( const unsigned short int value );
		void setLang( const E_LANG_TYPE lang );

		// Methods for getting parameters
		bool getSoundEffects() const;
		bool getMusic() const;
		bool getAccelerometer() const;
		bool getVibration() const;
		unsigned short int getStartLevel() const;
		std::string getStartLevelStr() const;
		E_LANG_TYPE getLang() const;
		LangPack* getLangPack() const;

		std::multimap<long int,std::string,greater<long int> > getScores() const;
		void addNewScore( const std::string name, const long int value );
		long int getMinScore();

		void ReloadLang( const int id );
		std::string getString( const unsigned short int id );
};

inline void Config::setSoundEffects( const bool value )
{
	this->soundEffects = value;
}

inline void Config::setMusic( const bool value )
{
	this->music = value;
}

inline bool Config::getSoundEffects() const
{
	return soundEffects;
}

inline bool Config::getMusic() const
{
	return music;
}

inline void Config::setAccelerometer( const bool value )
{
	accelerometer = value;
}

inline bool Config::getAccelerometer() const
{
	return accelerometer;
}

inline void Config::setVibration( const bool value )
{
	vibration = value;
}

inline bool Config::getVibration() const
{
	return vibration;
}

inline unsigned short int Config::getStartLevel() const
{
	return startLevel;
}

inline std::string Config::getStartLevelStr() const
{
	char tmp[12] = "";
	sprintf( tmp, "%d", startLevel );
	return std::string( tmp );
}

inline void Config::setStartLevel( const unsigned short int value )
{
	startLevel = value;
}

inline void Config::setLang( const E_LANG_TYPE lang )
{
	this->lang = lang;
}

inline E_LANG_TYPE Config::getLang() const
{
	return lang;
}

inline LangPack* Config::getLangPack() const
{
	return langpack;
}

inline void Config::ReloadLang( const int id )
{
	langpack->ReadPack( id );
}

inline std::string Config::getString( const unsigned short int id )
{
	return langpack->GetString(id);
}

inline std::multimap<long int,std::string,greater<long int> > Config::getScores() const
{
	return scores;
}

#endif