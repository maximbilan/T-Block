#include "PlatformPrecomp.h"
#include "Entity/EntityUtils.h"
#include "GUI_Game.h"
#include "GUI_MainMenu.h"
#include "GUI_InputBestScore.h"
#include "GameLogic/Tetris.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "XMLMenu/XMLMenu.h"
#include "Defines/GUI_IDs.h"

#include "GameStates/GS_Menu.h"

void buttonMoveSound()
{
	Config* config = Config::GetInstance();
	if( config->getSoundEffects() )
	{
		GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_FIGURE_MOVE ) );
	}

	config->FreeInstance();
}

void GameOnSelect( VariantList* pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();

	Tetris* tetris = Tetris::GetInstance();
	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_MENU_BUTTON )
	{
		GetApp()->buttonClickSound();

		if( tetris->isEndGame() )
		{
			SlideScreen( pEntClicked->GetParent(), false );
			GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		
			GetApp()->setGame( false );
			GetApp()->setContinueBtn( false );

			if( tetris->getScoreInt() > config->getMinScore() )
			{
				GameState::SetState( new GS_Menu() );
				InputBestScoreCreate( pEntClicked->GetParent()->GetParent() );
			}
			else
			{
				tetris->ResetEndGame();

				GameState::SetState( new GS_Menu() );
				MainMenuCreate( pEntClicked->GetParent()->GetParent() );
			}
		
			tetris->FreeInstance();
			config->FreeInstance();

			return;
		}

		GameState::SetState( new GS_Menu() );

		if( config->getMusic() )
		{
			GetAudioManager()->StopMusic();
		}
		
		GetApp()->setGame( false );
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_DOWN && !tetris->isEndGame() )
	{
		if( config->getSoundEffects() )
		{
			GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_FIGURE_DOWN ) );
		}
		tetris->ClickForceDown();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_LEFT && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickLeft();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_RIGHT && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickRight();
	}

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_GAMEPLAY_ROTATE && !tetris->isEndGame() )
	{
		buttonMoveSound();
		tetris->ClickRotate();
	}

	tetris->FreeInstance();
	config->FreeInstance();
}

Entity* GameCreate( Entity* pParentEnt )
{
	Config* config = Config::GetInstance();
	
	GetApp()->setContinueBtn( true );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_gameMenuXml );

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &GameOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGE_GAMEOVER_SPLASH );
	if( pEnt )
	{
		pEnt->GetVar( "visible" )->Set( uint32( 0 ) );
	}

	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_GAMEPLAY_DOWN );
	if( pEnt )
	{
		 pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_GAMEPLAY_LEFT );
	if( pEnt )
	{
		 pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_GAMEPLAY_RIGHT );
	if( pEnt )
	{
		 pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGEBUTTON_GAMEPLAY_ROTATE );
	if( pEnt )
	{
		 pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}

	GetApp()->setGame( true );

	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}