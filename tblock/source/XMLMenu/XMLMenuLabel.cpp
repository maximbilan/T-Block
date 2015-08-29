#include "PlatformPrecomp.h"
#include "XMLMenuLabel.h"
#include "XMLMenuHelper.h"

XMLMenuLabel::XMLMenuLabel()
	: m_textID( "" ), 
	  m_underlined( false ),
	  m_fontSize( 0 ),
	  m_alignment( 0 ),
	  m_isInputBox( false )
{
	m_type = EXMT_LABEL;
	
	int index = static_cast< int >( m_type );
	m_typeStr = XML_MENU_TYPE_STR[ index ];
}

XMLMenuLabel::~XMLMenuLabel()
{
}

void XMLMenuLabel::ReadFromXML( TiXmlElement* element )
{
	TiXmlAttribute* attrib = element->FirstAttribute();
		
	while( attrib )
	{
		if( strcmp( attrib->Name(), "text_id" ) == 0 )
		{
			m_textID = const_cast< char* >( attrib->Value() );
		}
		else if( strcmp( attrib->Name(), "underlined" ) == 0 )
		{
			m_underlined = XMLMenuHelper::charToBool( const_cast< char* >( attrib->Value() ) );
		}
		else if( strcmp( attrib->Name(), "back_button" ) == 0 )
		{
			m_backButton = XMLMenuHelper::charToBool( const_cast< char* >( attrib->Value() ) );
		}
		else if( strcmp( attrib->Name(), "fontsize" ) == 0 )
		{
			sscanf( attrib->Value(), "%d", &m_fontSize );
		}
		else if( strcmp( attrib->Name(), "alignment" ) == 0 )
		{
			m_alignment = XMLMenuHelper::convertAlignmentStrToInt( attrib->Value() );
		}
		else if( strcmp( attrib->Name(), "inputtextbox" ) == 0 )
		{
			m_isInputBox = XMLMenuHelper::charToBool( const_cast< char* >( attrib->Value() ) );
		}
		else
		{
			setAttribs( attrib->Name(), const_cast< char* >( attrib->Value() ) );
		}

		attrib = attrib->Next();
	}
}