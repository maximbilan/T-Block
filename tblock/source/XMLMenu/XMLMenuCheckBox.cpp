#include "PlatformPrecomp.h"
#include "XMLMenuCheckBox.h"
#include "XMLMenuHelper.h"

XMLMenuCheckBox::XMLMenuCheckBox()
	: m_imageOnName( "" ),
	  m_imageOffName( "" ),
	  m_textID( "" )
{
	m_type = EXMT_CHECKBOX;
	
	int index = static_cast< int >( m_type );
	m_typeStr = XML_MENU_TYPE_STR[ index ];
}

XMLMenuCheckBox::~XMLMenuCheckBox()
{
}

void XMLMenuCheckBox::ReadFromXML( TiXmlElement* element )
{
	TiXmlAttribute* attrib = element->FirstAttribute();
		
	while( attrib )
	{
		if( strcmp( attrib->Name(), "image_on" ) == 0 )
		{
			m_imageOnName = const_cast< char* >( attrib->Value() );
		}
		else if( strcmp( attrib->Name(), "image_off" ) == 0 )
		{
			m_imageOffName = const_cast< char* >( attrib->Value() );
		}
		else if( strcmp( attrib->Name(), "text_id" ) == 0 )
		{
			m_textID = const_cast< char* >( attrib->Value() );
		}
		else
		{
			setAttribs( attrib->Name(), const_cast< char* >( attrib->Value() ) );
		}

		attrib = attrib->Next();
	}
}