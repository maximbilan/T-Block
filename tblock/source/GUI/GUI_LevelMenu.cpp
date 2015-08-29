#include "PlatformPrecomp.h"
#include "GUI_Options.h"
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

void LevelMenuOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_LEVEL_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_LEVEL_OPTIONS_LEFT )
	{
		GetApp()->buttonClickSound();
		if( config->getStartLevel() > 1 )
		{
			config->setStartLevel( config->getStartLevel() - 1 );
			config->Save();
		}
		Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_LEVEL_TEXT_PARAMETER );
		if( pEnt )
		{
			pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( config->getStartLevelStr() );
		}
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_LEVEL_OPTIONS_RIGHT )
	{
		GetApp()->buttonClickSound();
		if( config->getStartLevel() < 10 )
		{
			config->setStartLevel( config->getStartLevel() + 1 );
			config->Save();
		}
		
		Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_LEVEL_TEXT_PARAMETER );
		if( pEnt )
		{
			pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( config->getStartLevelStr() );
		}
	}

	config->FreeInstance();
}

Entity* LevelMenuCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_levelMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &LevelMenuOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;
	
	Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_LEVEL_TEXT_PARAMETER );
	if( pEnt )
	{
		pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( config->getStartLevelStr() );
	}

	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_LEVEL_OPTIONS_LEFT );
	if( pEnt )
	{
		pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}

	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_LEVEL_OPTIONS_RIGHT );
	if( pEnt )
	{
		pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}

	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}