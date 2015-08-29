#ifndef _LangPack_H_
#define _LangPack_H_

#include "vector"
#include <map>
#include "string.h"

class LangPack
{
	private:
		std::vector<std::string> m_strings;
		std::map<std::string, unsigned int> m_ids;

	public:
		LangPack();
		~LangPack();

		void ReadPack( unsigned short int lang );
		std::string GetString( unsigned short int id );
		std::string GetString( const char* textID );
};

#endif