#include "PlatformPrecomp.h"
#include "GS_GamePlay.h"
#include "GameLogic/Tetris.h"
#include "App.h"
#include "Defines/LangIDS.h"
#include "Defines/GUI_IDs.h"

GS_GamePlay::GS_GamePlay()
{
	m_tetris = Tetris::GetInstance();
	m_config = Config::GetInstance();
}

GS_GamePlay::~GS_GamePlay()
{
	m_tetris->FreeInstance();
	m_config->FreeInstance();
}

void GS_GamePlay::ResumeState()
{
}

void GS_GamePlay::UpdateState( int frameTime )
{
	Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_LEVEL_LABEL_BOX );
	if( pEnt )
	{
		pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( m_tetris->getLevel() );
	}

	pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_SCORE_LABEL_BOX );
	if( pEnt )
	{
		pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( m_tetris->getScore() );
	}

	pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_LINES_LABEL_BOX );
	if( pEnt )
	{
		pEnt->GetComponentByName( "TextRender" )->GetVar( "text" )->Set( m_tetris->getLines() );
	}
}

void GS_GamePlay::RenderState()
{
	if( m_tetris->isEndGame() )
	{
		Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGE_GAMEOVER_SPLASH );
		if( pEnt )
		{
			pEnt->GetVar( "visible" )->Set( uint32( 1 ) );
			pEnt->GetVar( "rotation" )->Set( Variant( SinGamePulseByMS(1500)*0.5f ) );
		}

		pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGE_GAMEPLAY_MARK );
		if( pEnt )
		{
			pEnt->GetVar( "visible" )->Set( uint32( 0 ) );
		}
	}

	m_tetris->Run();
}