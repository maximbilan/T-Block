#ifndef _XMLMenuCHECKBOX_H_
#define _XMLMenuCHECKBOX_H_

#include "XMLMenuElement.h"

class XMLMenuCheckBox : public XMLMenuElement
{
	private:
		std::string m_imageOnName;
		std::string m_imageOffName;
		std::string m_textID;

	public:
		XMLMenuCheckBox();
		virtual ~XMLMenuCheckBox();

		std::string getImageOnName() const;
		std::string getImageOffName() const;
		std::string getTextID() const;

		virtual void ReadFromXML( TiXmlElement* element );
};

inline std::string XMLMenuCheckBox::getImageOnName() const
{
	return m_imageOnName;
}

inline std::string XMLMenuCheckBox::getImageOffName() const
{
	return m_imageOffName;
}

inline std::string XMLMenuCheckBox::getTextID() const
{
	return m_textID;
}

#endif