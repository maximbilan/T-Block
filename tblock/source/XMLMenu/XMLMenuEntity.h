#ifndef _XMLMenuENTITY_H_
#define _XMLMenuENTITY_H_

#include "EXMLMenuTypes.h"
#include "tinyxml.h"

class XMLMenuEntity
{
	protected:
		E_XML_MENU_TYPE m_type;
		std::string		m_typeStr;

	public:
		XMLMenuEntity();
		XMLMenuEntity( const XMLMenuEntity &entity );
		XMLMenuEntity& operator = ( const XMLMenuEntity &entity );
		virtual ~XMLMenuEntity();

		E_XML_MENU_TYPE getType() const;
		std::string		getTypeStr() const;

		virtual void	ReadFromXML( TiXmlElement* element ) = 0;
};

inline E_XML_MENU_TYPE XMLMenuEntity::getType() const
{
	return m_type;
}

inline std::string XMLMenuEntity::getTypeStr() const
{
	int index = static_cast< int >( m_type );
	return XML_MENU_TYPE_STR[ index ];
}

#endif