#ifndef _XMLMenuLABEL_H_
#define _XMLMenuLABEL_H_

#include "XMLMenuElement.h"
#include "XMLMenuButton.h"

class XMLMenuLabel : public XMLMenuElement, public XMLMenuButton
{
	private:
		std::string m_textID;
		bool		m_underlined;
		int			m_fontSize;
		int			m_alignment;
		bool		m_isInputBox;

	public:
		XMLMenuLabel();
		virtual ~XMLMenuLabel();

		std::string getTextID() const;
		bool		isUnderlined() const;
		int			getFontSize() const;
		int			getAlignment() const;
		bool		isInputBox() const;


		virtual void ReadFromXML( TiXmlElement* element );
};

inline std::string XMLMenuLabel::getTextID() const
{
	return m_textID;
}

inline bool XMLMenuLabel::isUnderlined() const
{
	return m_underlined;
}

inline int XMLMenuLabel::getFontSize() const
{
	return m_fontSize;
}

inline int XMLMenuLabel::getAlignment() const
{
	return m_alignment;
}

inline bool XMLMenuLabel::isInputBox() const
{
	return m_isInputBox;
}

#endif