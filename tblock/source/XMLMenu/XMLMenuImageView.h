#ifndef _XMLMenuIMAGEVIEW_H_
#define _XMLMenuIMAGEVIEW_H_

#include "XMLMenuElement.h"
#include "XMLMenuButton.h"

class XMLMenuImageView : public XMLMenuElement, public XMLMenuButton
{
	private:
		std::string m_imageName;

	public:
		XMLMenuImageView();
		virtual ~XMLMenuImageView();

		std::string getImageName() const;

		virtual void ReadFromXML( TiXmlElement* element );
};

inline std::string XMLMenuImageView::getImageName() const
{
	return m_imageName;
}

#endif