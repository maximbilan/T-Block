#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "Entity/EntityUtils.h"
#include "GUI_Game.h"
#include "GUI_Options.h"
#include "GUI_Scores.h"
#include "GUI_About.h"
#include "GUI_InputBestScore.h"
#include "GUI_SplashScreen.h"
#include "Entity/CustomInputComponent.h"
#include "GameLogic/Tetris.h"
#include "Utils/LangPack.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"
#include "GameStates/GS_GamePlay.h"
#include "Defines/GUI_IDs.h"

void MainMenuOnSelect( VariantList* pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();
	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_PLAY_BUTTON )
	{
		Tetris* tetris = Tetris::GetInstance();
		tetris->Reset();
		tetris->FreeInstance();

		GameState::SetState( new GS_GamePlay() );

		GetApp()->buttonClickSound();
		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		GameCreate(pEntClicked->GetParent()->GetParent());
		
		
		if( config->getMusic() )
		{
			if( GetPlatformID() == PLATFORM_ID_BBX )
			{
				GetAudioManager()->Play(GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_THEME ), true, true );
			}
			else
			{
				GetAudioManager()->Play( "audio/theme.mp3", true, true );
			}
		}

		if (config->getVibration()) {
			GetAudioManager()->Vibrate();
		}
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_OPTIONS_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		OptionsCreate(pEntClicked->GetParent()->GetParent());
	
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_INFO_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		AboutCreate(pEntClicked->GetParent()->GetParent());
	
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_SCORES_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		ScoresCreate(pEntClicked->GetParent()->GetParent());
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_CONTINUE_BUTTON )
	{
		GameState::SetState( new GS_GamePlay() );
		GetApp()->buttonClickSound();

		if( config->getMusic() )
		{
			if( GetPlatformID() == PLATFORM_ID_BBX )
			{
				GetAudioManager()->Play(GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_THEME ), true, true );
			}
			else
			{
				GetAudioManager()->Play( "audio/theme.mp3", true, true );
			}
		}

		if (config->getVibration()) {
			GetAudioManager()->Vibrate();
		}

		SlideScreen(pEntClicked->GetParent(), false);
		GetMessageManager()->CallEntityFunction(pEntClicked->GetParent(), 500, "OnDelete", NULL);
		GameCreate(pEntClicked->GetParent()->GetParent());
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_MM_EXIT_BUTTON )
	{
		GetApp()->buttonClickSound();
		exit( 0 );
	}

	config->FreeInstance();
}

Entity* MainMenuCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_main );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_mainMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &MainMenuOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	if( !GetApp()->isContinue() )
	{	
		Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_MM_TEXT_CONTINUE );
		if( pEnt )
		{
			pEnt->GetVar( "visible" )->Set( uint32( 0 ) );
		}
		pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_MM_CONTINUE_BUTTON );
		if( pEnt )
		{
			pEnt->GetVar( "visible" )->Set( uint32( 0 ) );
		}
	}

	FadeInEntity(pBG, true, 1000);

	config->FreeInstance();

	return pBG;
}

