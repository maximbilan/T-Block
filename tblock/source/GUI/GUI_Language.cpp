#include "PlatformPrecomp.h"
#include "GUI_Options.h"
#include "GUI_Language.h"
#include "Entity/EntityUtils.h"
#include "Config/Config.h"
#include "Defines/Langs.h"
#include <string>
#include "Defines/LangIDS.h"
#include "XMLMenu/XMLMenu.h"
#include "Defines/GameConstants.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"
#include "Defines/GUI_IDs.h"

void LanguageOnSelect( VariantList *pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();

	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_LANGUAGE_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_FLAG_EN_BUTTON )
	{
		GetApp()->buttonClickSound();
		config->setLang( convertCodeToId( LANG_NAMES[ LANG_EN ] ) );
		config->Save();
		config->ReloadLang( LANG_EN );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_FLAG_RU_BUTTON )
	{
		GetApp()->buttonClickSound();
		config->setLang( convertCodeToId( LANG_NAMES[ LANG_RU ] ) );
		config->Save();
		config->ReloadLang( LANG_RU );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	config->FreeInstance();
}

Entity* LanguageCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_languagesMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &LanguageOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;
	
	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}