#include "PlatformPrecomp.h"
#include "XMLMenuElement.h"
#include "XMLMenuHelper.h"
#include <string>

XMLMenuElement::XMLMenuElement()
	: m_class( EXMC_NONE ), m_classStr( "" ), m_id( "" ), m_enabled( false ), m_x1( 0 ), m_y1( 0 ), m_x2( 0 ), m_y2( 0 ), m_width( 0 ), m_height( 0 )
{
}

XMLMenuElement::XMLMenuElement( const XMLMenuElement &element )
{
	operator = ( element );
}

XMLMenuElement& XMLMenuElement::operator = ( const XMLMenuElement &element )
{
	if( this == &element )
	{
		return *this;
	}

	XMLMenuEntity::operator = ( element );
	
	m_class = element.m_class;
	m_classStr = element.m_classStr;
	m_id = element.m_id;
	m_enabled = element.m_enabled;
	m_x1 = element.m_x1;
	m_y1 = element.m_y1;
	m_x2 = element.m_x2;
	m_y2 = element.m_y2;
	m_width = element.m_width;
	m_height = element.m_height;

	return *this;
}

XMLMenuElement::~XMLMenuElement()
{
}

void XMLMenuElement::setAttribs( const char* attrib, char* value )
{

	if( strcmp( attrib, "class" ) == 0 )
	{
		m_classStr = value;
		m_class = convertClassNameToID( value );
	}
	else if( strcmp( attrib, "id" ) == 0 )
	{
		m_id = value;
	}
	else if( strcmp( attrib, "enabled" ) == 0 )
	{
		m_enabled = XMLMenuHelper::charToBool( value );
	}
	else if( strcmp( attrib, "dist_tl_x" ) == 0 )
	{
		sscanf( value, "%d", &m_x1 );
	}
	else if( strcmp( attrib, "dist_tl_y" ) == 0 )
	{
		sscanf( value, "%d", &m_y1 );
	}
	else if( strcmp( attrib, "dist_br_x" ) == 0 )
	{
		sscanf( value, "%d", &m_x2 );
	}
	else if( strcmp( attrib, "dist_br_y" ) == 0 )
	{
		sscanf( value, "%d", &m_y2 );
	}
	else if( strcmp( attrib, "width" ) == 0 )
	{
		sscanf( value, "%d", &m_width );
	}
	else if( strcmp( attrib, "height" ) == 0 )
	{
		sscanf( value, "%d", &m_height );
	}
		 
}