#ifndef _XMLMenu_H_
#define _XMLMenu_H_

#include "tinyxml.h"
#include "XMLMenuImageView.h"
#include "XMLMenuLabel.h"
#include "XMLMenuCheckBox.h"
#include <vector>
#include "Entity/EntityUtils.h"
#include "Utils/LangPack.h"

typedef void (*ExternalFunc)( VariantList *pVList );

class XMLMenu
{
	private:
		const char* m_fileName;
		std::vector<XMLMenuImageView*> m_vecImageViews;
		std::vector<XMLMenuLabel*> m_vecLabels;
		std::vector<XMLMenuCheckBox*> m_vecCheckBoxes;
		Entity* m_parentEntity;
		ExternalFunc m_OnSelectFunc;
		LangPack* m_langPack;

		void Parse( TiXmlNode* pParent );
		void readFile( const char* pFilename );

	public:
		XMLMenu( const char* fileName, Entity* parentEntity, ExternalFunc selectFunc, LangPack* langPack );
		~XMLMenu();

		std::vector<XMLMenuImageView*> getVecImageViews() const;
		std::vector<XMLMenuLabel*>	   getVecLabels() const;
		std::vector<XMLMenuCheckBox*>  getVecCheckBoxes() const;
		Entity* createEntities();
		void createEntities( Entity* pEntity );

		void Read();

};

inline std::vector<XMLMenuImageView*> XMLMenu::getVecImageViews() const
{
	return m_vecImageViews;
}

inline std::vector<XMLMenuLabel*> XMLMenu::getVecLabels() const
{
	return m_vecLabels;
}

inline std::vector<XMLMenuCheckBox*>  XMLMenu::getVecCheckBoxes() const
{
	return m_vecCheckBoxes;
}

#endif