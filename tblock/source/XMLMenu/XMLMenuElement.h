#ifndef _XMLMenuELEMENT_H_
#define _XMLMenuELEMENT_H_

#include "EXMLMenuTypes.h"
#include "XMLMenuEntity.h"
#include <string>

class XMLMenuElement : public XMLMenuEntity
{
	protected:
		E_XML_MENU_CLASS m_class;
		std::string		 m_classStr;
		
		std::string		 m_id;
		bool			 m_enabled;

		int				 m_x1;
		int				 m_y1;
		int				 m_x2;
		int				 m_y2;

		int				 m_width;
		int				 m_height;

	public:
		XMLMenuElement();
		XMLMenuElement( const XMLMenuElement &element );
		XMLMenuElement& operator = ( const XMLMenuElement &element );
		virtual ~XMLMenuElement();

		E_XML_MENU_CLASS getClass() const;
		std::string		 getClassStr() const;
		std::string		 getID() const;
		
		bool			 isEnabled() const;
		
		int				 getX1() const;
		int				 getY1() const;
		int				 getX2() const;
		int				 getY2() const;

		int				 getWidth() const;
		int				 getHeight() const;

		void			 setAttribs( const char* attrib, char* value );
		virtual void	 ReadFromXML( TiXmlElement* element ) = 0;
};

inline E_XML_MENU_CLASS XMLMenuElement::getClass() const
{
	return m_class;
}

inline std::string XMLMenuElement::getClassStr() const
{
	int index = static_cast< int >( m_class );
	return XML_MENU_CLASS_STR[ index ];
}

inline std::string XMLMenuElement::getID() const
{
	return m_id;
}

inline bool XMLMenuElement::isEnabled() const
{
	return m_enabled;
}
	
inline int XMLMenuElement::getX1() const
{
	return m_x1;
}

inline int XMLMenuElement::getY1() const
{
	return m_y1;
}

inline int XMLMenuElement::getX2() const
{
	return m_x2;
}

inline int XMLMenuElement::getY2() const
{
	return m_y2;
}

inline int XMLMenuElement::getWidth() const
{
	return m_width;
}

inline int XMLMenuElement::getHeight() const
{
	return m_height;
}

#endif