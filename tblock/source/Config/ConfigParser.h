#ifndef _CONFIGPARSER_H_
#define _CONFIGPARSER_H_

#include <string>
#include <map>
#include <list>

/*
   ConfigParser

   Parse structured config files

   Config files contains lines with name-value assignements in the form "<name> = <value>".
   Trailing and leading whitespace is stripped. Parsed config entries are stored in
   a symbol map.
   
   Lines beginning with '#' are a comment and ignored.

   Config files may be structured (to arbitrary depth). To start a new config sub group
   (or sub section) use a line in the form of "<name> = (".
   Subsequent entries are stured in the sub group, until a line containing ")" is found.

   Values may reuse already defined names as a variable which gets expanded during
   the parsing process. Names for expansion are searched from the current sub group
   upwards. Finally the process environment is searched, so also environment
   variables may be used as expansion symbols in the config file.

   Errors and warnings are handled by emitting logging messages (see log.h/log.cpp)
   or by calling exit() for severe errors. Depending on project needs this may be replaced
   by exeptions, error return codes, ...
 */

class ConfigParser
{
	public:
		/* Parse config file 'configFile'. If the process environment
		 * is provided, environment variables can be used as expansion symbols.
		 */
		ConfigParser( std::string configFile, char** envp = 0 );

		~ConfigParser();
		
		// get string config entry
		std::string pString( std::string name );

		/* get boolean config entry
		 * A value of Yes/yes/YES/true/True/TRUE leads to true,
		 * all other values leads to false.
		 */
		bool pBool( std::string name );

		// get double config entry; value is parsed using atof()
		double pDouble( std::string name );

		// get int config entry; value is parsed using atoi()
		int pInt( std::string name );

		// get the symbol map (e.g. for iterating over all symbols)
		inline std::map<std::string, std::string>& getSymbols()
		{
			return symbols;
		}

		// get config sub group
		inline ConfigParser* group( std::string name )
		{
			return groups[name];
		}

		// get config sub group map (e.g. for iterating over all groups)
		inline std::map<std::string, ConfigParser*>& getGroups()
		{
			return groups;
		}

		bool isParsed();

	private:
		// private constructor for sub groups
		ConfigParser( std::string name, std::string parentDebugInfo );

		// helper functions for parsing
		void add( std::string name, std::string value );
		void split( std::string in, std::string& left, std::string& right, char c );
		void trim( std::string& s );
		void symbolExpand( std::string& s );
		void symbolExpand( std::map<std::string, std::string>& symbols, std::string& s );
		void envSymbolExpand( std::string& s );
		
		// config group symbol map
		std::map<std::string, std::string> symbols;

		// environment symbol map
		std::map<std::string, std::string> envSymbols;

		// config sub group map
		std::map<std::string, ConfigParser*> groups;

		// stack of config groups for parsing (only used in top config element)
		std::list<ConfigParser*> groupStack;

		// debug info used for logging messages
		std::string debugInfo;

		bool parseFailed;
};

#endif