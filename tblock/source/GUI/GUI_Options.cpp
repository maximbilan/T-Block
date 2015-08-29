#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "GUI_Options.h"
#include "GUI_Language.h"
#include "GUI_Sound.h"
#include "GUI_LevelMenu.h"
#include "Entity/EntityUtils.h"
#include "Config/Config.h"
#include "Defines/Langs.h"
#include <string>
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"
#include "Defines/GUI_IDs.h"

void OptionsOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_OPTIONS_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_OPTIONS_LANGUAGE_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		LanguageCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_OPTIONS_SOUND_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		SoundCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_OPTIONS_LEVEL_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		LevelMenuCreate( pEntClicked->GetParent()->GetParent() );
	}

	config->FreeInstance();
}

Entity* OptionsCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_optionsMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &OptionsOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;
	
	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}