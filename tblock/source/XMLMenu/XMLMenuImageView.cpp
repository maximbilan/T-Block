#include "PlatformPrecomp.h"
#include "XMLMenuImageView.h"
#include "XMLMenuHelper.h"

XMLMenuImageView::XMLMenuImageView()
	: m_imageName( "" )
{
	m_type = EXMT_IMAGEVIEW;
	
	int index = static_cast< int >( m_type );
	m_typeStr = XML_MENU_TYPE_STR[ index ];
}

XMLMenuImageView::~XMLMenuImageView()
{
}

void XMLMenuImageView::ReadFromXML( TiXmlElement* element )
{
	TiXmlAttribute* attrib = element->FirstAttribute();
		
	while( attrib )
	{
		if( strcmp( attrib->Name(), "image_name" ) == 0 )
		{
			m_imageName = const_cast< char* >( attrib->Value() );
		}
		else if( strcmp( attrib->Name(), "back_button" ) == 0 )
		{
			m_backButton = XMLMenuHelper::charToBool( const_cast< char* >( attrib->Value() ) );
		}
		else
		{
			setAttribs( attrib->Name(), const_cast< char* >( attrib->Value() ) );
		}

		attrib = attrib->Next();
	}
}