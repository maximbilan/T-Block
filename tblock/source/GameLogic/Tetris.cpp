#include "PlatformPrecomp.h"
#include "Tetris.h"
#include "GUI/GUI_MainMenu.h"
#include "Defines/GameScaleValues.h"

void Tetris::Init()
{
	m_io = new Render();
	m_figures = new Figure();
	m_board = new Board( m_figures, SCREEN_HEIGHT_GAME_VALUES[GetApp()->getResolutionType()] );
	m_game = new Game( m_board, m_figures, m_io, SCREEN_HEIGHT_GAME_VALUES[GetApp()->getResolutionType()] );
	m_timer = new Timer();
	m_config = Config::GetInstance();

	m_timer->start();

	m_tick1 = m_timer->getElapsedTimeInMilliSec();
	m_tick2 = m_tick1;

	m_endGame = false;
}

void Tetris::Reset()
{
	m_game->Reset();
}

void Tetris::Run()
{
	
	if( !m_endGame )
	{
		m_game->DrawScene();

		// ----- Vertical movement -----
	
		m_tick2 = m_timer->getElapsedTimeInMilliSec();

		if( ( m_tick2 - m_tick1 ) > WAIT_TIME - ( ( m_board->getLevel() - 1 ) * 60 ) )
		{

			if( m_board->IsPossibleMovement( m_game->getPosX(), m_game->getPosY() + 1, m_game->getFigure(), m_game->getRotation() ) )
			{
				int posY = m_game->getPosY() + 1;
				m_game->setPosY( posY );
			}
			else
			{
				m_board->StoreFigure( m_game->getPosX(), m_game->getPosY(), m_game->getFigure(), m_game->getRotation(), m_game->getColor() );
				m_board->DeletePossibleLines ();
	
				m_game->CreateNewPiece();

				if( m_board->IsGameOver() )
				{
					m_endGame = true;
					m_board->InitBoard();

					if( m_config->getMusic() )
					{
						GetAudioManager()->StopMusic();
					}

					if( m_config->getSoundEffects() )
					{
						GetAudioManager()->Play(GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_GAME_OVER ) );
					}

					if( m_config->getVibration() )
					{
						GetAudioManager()->Vibrate();
					}

				}
				
			}

			m_tick1 = m_timer->getElapsedTimeInMilliSec();
		}
	}
	else
	{
		m_game->DrawGameOver();
	}

}

void Tetris::Delete()
{
	m_config->FreeInstance();

	delete (Render*) m_io;
	delete (Figure*) m_figures;
	delete (Board*) m_board;
	delete (Game*) m_game;
	delete (Timer*) m_timer;
}

void Tetris::ClickLeft()
{
	if( m_board->IsPossibleMovement( m_game->getPosX() - 1, m_game->getPosY(), m_game->getFigure(), m_game->getRotation() ) )
	{
		int posX = m_game->getPosX() - 1;
		m_game->setPosX( posX );
	}
}

void Tetris::ClickRight()
{
	if( m_board->IsPossibleMovement( m_game->getPosX() + 1, m_game->getPosY(), m_game->getFigure(), m_game->getRotation() ) )
	{
		int posX = m_game->getPosX() + 1;
		m_game->setPosX( posX );
	}
}

void Tetris::ClickRotate()
{
	if( m_board->IsPossibleMovement( m_game->getPosX(), m_game->getPosY(), m_game->getFigure(), ( m_game->getRotation() + 1 ) % 4 ) )
	{
		int rotation = ( m_game->getRotation() + 1 ) % 4;
		m_game->setRotation( rotation );
	}
}

void Tetris::ClickDown()
{
	if( m_board->IsPossibleMovement( m_game->getPosX(), m_game->getPosY() + 1, m_game->getFigure(), m_game->getRotation() ) )
	{
		int posY = m_game->getPosY() + 1;
		m_game->setPosY( posY );
	}
}

void Tetris::ClickForceDown()
{

	while( m_board->IsPossibleMovement( m_game->getPosX(), m_game->getPosY(), m_game->getFigure(), m_game->getRotation() ) )
	{ 
		int posY = m_game->getPosY() + 1;
		m_game->setPosY( posY );
	}
	
	m_board->StoreFigure( m_game->getPosX(), m_game->getPosY() - 1, m_game->getFigure(), m_game->getRotation(), m_game->getColor() );
	m_board->DeletePossibleLines();
	m_game->CreateNewPiece();
}