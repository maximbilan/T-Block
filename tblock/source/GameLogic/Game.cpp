#include "PlatformPrecomp.h"
#include "Game.h"
#include <stdio.h>
#include <stdlib.h>
#include "GUI/GUI_MainMenu.h"
#include "Defines/GameScaleValues.h"

Game::Game()
{
}

Game::Game( Board *board, Figure *figures, Render *io, int screenHeight )
{
	m_screenHeight = screenHeight;

	// Get the pointer to the Board and Pieces classes
	m_board = board;
	m_figures = figures;
	m_io = io;

	// Game initialization
	InitGame();
}

Game::~Game()
{
}

int Game::GetRand( const int a, const int b )
{
	return rand() % ( b - a + 1 ) + a;
}

void Game::InitGame()
{
	// Init random numbers
	srand( (unsigned int)time( NULL ) );

	// First piece
	m_figure	= GetRand( 0, 6 );
	m_rotation	= GetRand( 0, 3 );
	m_color     = (E_TYPE_COLOR) GetRand( 0, 7 );
	m_posX 		= ( BOARD_WIDTH / 2 ) + m_figures->GetXInitialPosition( m_figure, m_rotation );
	m_posY 		= m_figures->GetYInitialPosition( m_figure, m_rotation );

	//  Next piece
	m_nextFigure 	= GetRand( 0, 6 );
	m_nextRotation 	= GetRand( 0, 3 );
	m_nextColor     = (E_TYPE_COLOR) GetRand( 0, 7 );
	m_nextPosX 		= BOARD_WIDTH + NEXT_FIGURE_POSITION_X_VALUES[ GetApp()->getResolutionType() ];
	m_nextPosY 		= 2 + NEXT_FIGURE_POSITION_Y_VALUES[ GetApp()->getResolutionType() ];
}

void Game::DrawPiece( const int x, const int y, const int figure, const int rotation, const E_TYPE_COLOR color, bool nextFigure )
{
	// Obtain the position in pixel in the screen of the block we want to draw
	int _pixelsX = m_board->GetXPosInPixels( x );
	int _pixelsY = m_board->GetYPosInPixels( y );

	// Travel the matrix of blocks of the piece and draw the blocks that are filled
	for( int i = 0; i < FIGURE_BLOCKS; i++ )
	{
		for( int j = 0; j < FIGURE_BLOCKS; j++ )
		{
			if( m_figures->GetBlockType( figure, rotation, j, i ) != 0 )
			{
				float scale = SCALE_GAME_VALUES[ GetApp()->getResolutionType() ];

				if( nextFigure )
				{
					scale *= NEXT_FIGURE_SCALE_VALUES[ GetApp()->getResolutionType() ];
				}

				float x = static_cast<float>( _pixelsX + i * scale );
				float y = static_cast<float>( _pixelsY + j * scale );
				
				if( nextFigure )
				{
					m_io->DrawRectangle( x, y, color, NEXT_FIGURE_SCALE_VALUES[ GetApp()->getResolutionType() ], NEXT_FIGURE_SCALE_VALUES[ GetApp()->getResolutionType() ] );
				}
				else
				{
					m_io->DrawRectangle( x, y, color );
				}

			}
		}
	}
}
	
void Game::DrawBoard()
{

	// Calculate the limits of the board in pixels	
	int mX1 = BOARD_POS_GAME_VALUES[ GetApp()->getResolutionType()] - ( SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] * ( BOARD_WIDTH / 2 ) ) - 1;
	int mX2 = BOARD_POS_GAME_VALUES[ GetApp()->getResolutionType()] + ( SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] * ( BOARD_WIDTH / 2 ) );
	int mY = m_screenHeight - ( SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] * BOARD_HEIGHT );
	
	int offset = 0;

	// Drawing the blocks that are already stored in the board
	mX1 += 1;
	for( int i = 0; i < BOARD_WIDTH; i++ )
	{
		for( int j = 0; j < BOARD_HEIGHT; j++ )
		{	
			// Check if the block is filled, if so, draw it
			if( !m_board->IsFreeBlock( i, j ) )
			{
				float pX = static_cast<float>( mX1 + i * SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] );
				float pY = static_cast<float>( mY + j * SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] );
				m_io->DrawRectangle( pX, pY, m_board->getColor( i, j )/*TC_YELLOW*/ );
			}
		}
	}	

}

void Game::DrawScene()
{
	DrawBoard();																			// Draw the delimitation lines and blocks stored in the board
	DrawPiece( m_posX, m_posY, m_figure, m_rotation, m_color );								// Draw the playing piece
	DrawPiece( m_nextPosX, m_nextPosY, m_nextFigure, m_nextRotation, m_nextColor, true );	// Draw the next piece
}

void Game::DrawGameOver()
{
	DrawBoard();																			// Draw the delimitation lines and blocks stored in the board
	DrawPiece( m_nextPosX, m_nextPosY, m_nextFigure, m_nextRotation, m_nextColor, true );	// Draw the next piece
}

void Game::CreateNewPiece()
{
	// The new piece
	m_figure	= m_nextFigure;
	m_rotation	= m_nextRotation;
	m_color     = m_nextColor;
	m_posX 		= ( BOARD_WIDTH / 2 ) + m_figures->GetXInitialPosition( m_figure, m_rotation );
	m_posY 		= m_figures->GetYInitialPosition( m_figure, m_rotation );

	// Random next piece
	m_nextFigure 	= GetRand( 0, 6 );
	m_nextRotation 	= GetRand( 0, 3 );
	m_nextColor     = (E_TYPE_COLOR)GetRand( 0, 7 );
}

void Game::Reset()
{
	m_board->Reset();
	InitGame();
}

void Game::ResetBoard()
{
	m_board->Reset();
}