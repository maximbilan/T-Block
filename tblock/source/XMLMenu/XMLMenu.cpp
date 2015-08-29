#include "PlatformPrecomp.h"
#include "XMLMenu.h"
#include "Utils/Resource.h"
#include "App.h"

XMLMenu::XMLMenu( const char* fileName, Entity* parentEntity, ExternalFunc selectFunc, LangPack* langPack )
	: m_fileName( fileName ), m_parentEntity( parentEntity ), m_OnSelectFunc( selectFunc ), m_langPack( langPack )
{
}

XMLMenu::~XMLMenu()
{
	vector<XMLMenuImageView*>::iterator it;
	for( it = m_vecImageViews.begin(); it != m_vecImageViews.end(); ++it )
	{
		delete (*it);
	}
	m_vecImageViews.clear();

	vector<XMLMenuLabel*>::iterator itLabel;
	for( itLabel = m_vecLabels.begin(); itLabel != m_vecLabels.end(); ++itLabel )
	{
		delete (*itLabel);
	}
	m_vecLabels.clear();

	vector<XMLMenuCheckBox*>::iterator itCheckBox;
	for( itCheckBox = m_vecCheckBoxes.begin(); itCheckBox != m_vecCheckBoxes.end(); ++itCheckBox )
	{
		delete (*itCheckBox);
	}
	m_vecCheckBoxes.clear();
}

void XMLMenu::Read()
{
	readFile( m_fileName );
}

Entity* XMLMenu::createEntities()
{
	Entity* pBG = m_parentEntity->AddEntity( new Entity );
	
	createEntities( pBG );

	return pBG;
}

void XMLMenu::createEntities( Entity* pEntity )
{
	std::vector<XMLMenuImageView*>::iterator itIV;
	std::vector<XMLMenuLabel*>::iterator itL;
	std::vector<XMLMenuCheckBox*>::iterator itCB;
	
	AddFocusIfNeeded( pEntity );

	Entity *pButtonEntity;

	for( itIV = m_vecImageViews.begin(); itIV != m_vecImageViews.end(); ++itIV )
	{
		std::string imgPath = GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_ATLAS, RES_ID_NONE ).c_str();
		std::string id = ( *itIV )->getID();
		float x1 = static_cast< float >( ( *itIV )->getX1() );
		float y1 = static_cast< float >( ( *itIV )->getY1() );

		switch( ( *itIV )->getClass() )
		{
			case EXMC_BACKGROUND:
			{
				//CreateOverlayEntity( pBG, id.c_str(), img.c_str(), x1, y1 );
				CreateOverlayCustomEntity( pEntity, id.c_str(), ( *itIV )->getImageName(), x1, y1, imgPath );
			}
			break;

			case EXMC_IMAGE:
			{
				CreateOverlayCustomEntity( pEntity, id.c_str(), ( *itIV )->getImageName(), x1, y1, imgPath );
			}
			break;

			case EXMC_IMAGEBUTTON:
			{
				pButtonEntity = CreateOverlayCustomButtonEntity( pEntity, id.c_str(), ( *itIV )->getImageName(), x1, y1, imgPath );
				pButtonEntity->GetShared()->GetFunction( "OnButtonSelected" )->sig_function.connect( m_OnSelectFunc );

				if( ( *itIV )->isBackButton() )
				{
					AddHotKeyToButton( pButtonEntity, VIRTUAL_KEY_BACK );
				}
			}
			break;

			default:
			{
			}
			break;
		}
	}

	for( itL = m_vecLabels.begin(); itL != m_vecLabels.end(); ++itL )
	{
		std::string id = ( *itL )->getID().c_str();
		float x1 = static_cast< float >( ( *itL )->getX1() );
		float y1 = static_cast< float >( ( *itL )->getY1() );
		std::string textID = ( *itL )->getTextID();
		bool isInputBox = ( *itL )->isInputBox();
		const int alignment = ( *itL )->getAlignment();

		switch( ( *itL )->getClass() )
		{
			case EXMC_TEXT:
			{
				Entity* entity;
				if( isInputBox )
				{
					float sizeX = static_cast<float>( ( *itL )->getWidth() );
					entity = CreateInputTextEntity( pEntity, id.c_str(), x1, y1, m_langPack->GetString( textID.c_str() ), sizeX, 0 );
				}
				else
				{
					entity = CreateTextLabelEntity( pEntity, id.c_str(), x1, y1, m_langPack->GetString( textID.c_str() ) );
				}

				entity->GetVar( "alignment" )->Set( uint32( alignment ) );
			}
			break;

			case EXMC_TEXTBUTTON:
			{
				pButtonEntity = CreateTextButtonEntity( pEntity, id.c_str(), x1, y1, m_langPack->GetString( textID.c_str() ), ( *itL )->isUnderlined() );
				pButtonEntity->GetShared()->GetFunction( "OnButtonSelected" )->sig_function.connect( m_OnSelectFunc );

				if( ( *itL )->isBackButton() )
				{
					AddHotKeyToButton( pButtonEntity, VIRTUAL_KEY_BACK );
				}
			}
			break;

			default:
			{
			}
			break;
		}
	}

	for( itCB = m_vecCheckBoxes.begin(); itCB != m_vecCheckBoxes.end(); ++itCB )
	{
		std::string id = ( *itCB )->getID().c_str();
		float x1 = static_cast< float >( ( *itCB )->getX1() );
		float y1 = static_cast< float >( ( *itCB )->getY1() );
		std::string textID = ( *itCB )->getTextID();

		switch( ( *itCB )->getClass() )
		{
			case EXMC_CHECKBOX:
			{
				Entity *pCheckbox;
				
				pCheckbox = CreateCheckbox( pEntity, id.c_str(), GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_INTERFACE, RES_ID_CHECKBOX_ON_OFF ), textID, x1, y1, true );
				pCheckbox->GetShared()->GetFunction( "OnButtonSelected" )->sig_function.connect( m_OnSelectFunc );
				//pCheckbox->GetVar("alignment")->Set(uint32(ALIGNMENT_DOWN_LEFT));
			}
			break;

			default:
			{
			}
			break;
		}
	}
}

void XMLMenu::Parse( TiXmlNode* pParent )
{
	if( !pParent )
	{
		return;
	}

	TiXmlNode* pChild;
	TiXmlText* pText;
	int t = pParent->Type();

	switch ( t )
	{
		case TiXmlNode::TINYXML_DOCUMENT:
		{
		}
		break;

		case TiXmlNode::TINYXML_ELEMENT:
		{

			if( strcmp( pParent->Value(), "imageview" ) == NULL )
			{
				XMLMenuImageView* imv = new XMLMenuImageView();
				imv->ReadFromXML( pParent->ToElement() );
				m_vecImageViews.push_back( imv );
			}
			else if( strcmp( pParent->Value(), "label" ) == NULL )
			{
				XMLMenuLabel* label = new XMLMenuLabel();
				label->ReadFromXML( pParent->ToElement() );
				m_vecLabels.push_back( label );
			}
			else if( strcmp( pParent->Value(), "checkbox" ) == NULL )
			{
				XMLMenuCheckBox* checkBox = new XMLMenuCheckBox();
				checkBox->ReadFromXML( pParent->ToElement() );
				m_vecCheckBoxes.push_back( checkBox );
			}

		}
		break;

		case TiXmlNode::TINYXML_COMMENT:
		{
		}
		break;

		case TiXmlNode::TINYXML_UNKNOWN:
		{
		}
		break;

		case TiXmlNode::TINYXML_TEXT:
		{
			pText = pParent->ToText();
		}
		break;

		case TiXmlNode::TINYXML_DECLARATION:
		{
		}
		break;

		default:
		{
		}
		break;
	
	}
	
	for( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling() )
	{
		Parse( pChild );
	}
}

void XMLMenu::readFile( const char* pFilename )
{
	bool f = GetFileManager()->FileExists( pFilename );
	if( f )
	{
		FileInstance file( pFilename );
		LogMsg( "I just loaded a file into memory that is %d bytes.", file.GetSize() );
		
		char temp[16384] = "";
		strcat( temp, file.GetAsChars() );

		TiXmlDocument doc;
		doc.Parse( file.GetAsChars(), 0 );
		Parse( &doc );
	}
	else
	{
		LogMsg( "Failed to load file \"%s\"\n", pFilename );
	}
}