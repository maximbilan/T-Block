#include "PlatformPrecomp.h"
#include "Board.h"
#include "GUI/GUI_MainMenu.h"
#include "Defines/GameScaleValues.h"
#include "Defines/GameConstants.h"

Board::Board()
{
}

Board::Board( Figure *figures, int screenHeight )
{
	// Get the screen height
	m_screenHeight = screenHeight;

	// Get the pointer to the pieces class
	m_figures = figures;

	m_config = Config::GetInstance();

	Reset();
}

Board::~Board()
{
	m_config->FreeInstance();
}

void Board::Reset()
{
	m_level = m_config->getStartLevel();
	m_score = 0;
	m_curLines = 0;
	m_lines = 0;
	m_linesLevel = 0;

	//Init the board blocks with free positions
	InitBoard();
}

void Board::InitBoard() 
{
	for( int i = 0; i < BOARD_WIDTH; i++ )
	{
		for( int j = 0; j < BOARD_HEIGHT; j++)
		{
			m_board[i][j] = BLOCK_FREE;
			m_boardColor[i][j] = TC_NONE;
		}
	}
}

void Board::DeleteLine( const int y )
{

	if( m_config->getSoundEffects() )
	{
		GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_ERASE_LINE ) );
	}

	if( m_config->getVibration() )
	{
		GetAudioManager()->Vibrate();
	}

	// Moves all the upper lines one row down
	for( int j = y; j > 0; j-- )
	{
		for( int i = 0; i < BOARD_WIDTH; i++ )
		{
			m_board[i][j] = m_board[i][j-1];
			m_boardColor[i][j] = m_boardColor[i][j-1];
		}
	}
	m_curLines++;
}

bool Board::IsFreeBlock( const int x, const int y)
{
	if( m_board[x][y] == BLOCK_FREE )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::IsPossibleMovement( const int x, const int y, const int figure, const int rotation )
{
	
	// Checks collision with pieces already stored in the board or the board limits
	// This is just to check the 5x5 blocks of a piece with the appropiate area in the board
	for( int i1 = x, i2 = 0; i1 < x + FIGURE_BLOCKS; i1++, i2++ )
	{
		for( int j1 = y, j2 = 0; j1 < y + FIGURE_BLOCKS; j1++, j2++ )
		{	
			// Check if the piece is outside the limits of the board
			if( i1 < 0 || i1 > BOARD_WIDTH - 1 || j1 > BOARD_HEIGHT - 1 )
			{
				if( m_figures->GetBlockType( figure, rotation, j2, i2) != 0 )
				{
					return 0;
				}
			}

			// Check if the piece have collisioned with a block already stored in the map
			if( j1 >= 0 )
			{
				if( ( m_figures->GetBlockType( figure, rotation, j2, i2) != 0 ) && ( !IsFreeBlock( i1, j1 ) ) )
				{
					return false;
				}
			}
		}
	}

	// No collision
	return true;
}

void Board::StoreFigure( const int x, const int y, const int figure, const int rotation, const E_TYPE_COLOR color )
{
	// Store each block of the piece into the board
	for( int i1 = x, i2 = 0; i1 < x + FIGURE_BLOCKS; i1++, i2++ )
	{
		for( int j1 = y, j2 = 0; j1 < y + FIGURE_BLOCKS; j1++, j2++ )
		{	
			// Store only the blocks of the piece that are not holes
			if( m_figures->GetBlockType( figure, rotation, j2, i2 ) != 0 )
			{
				m_board[i1][j1] = BLOCK_FILLED;
				m_boardColor[i1][j1] = color;
			}
		}
	}
}

void Board::DeletePossibleLines()
{
	m_curLines = 0;
	for( int j = 0; j < BOARD_HEIGHT; j++ )
	{
		int i = 0;
		while( i < BOARD_WIDTH )
		{
			if( m_board[i][j] != BLOCK_FILLED )
			{
				break;
			}
			i++;
		}

		if( i == BOARD_WIDTH )
		{
			DeleteLine( j );
		}
	}

	m_lines += m_curLines;
	m_linesLevel += m_curLines;

	switch( m_curLines )
	{
		case 1:
		{
			m_score += s_scoresLevel1;
		}
		break;
		case 2:
		{
			m_score += s_scoresLevel2;
		}
		break;
		case 3:
		{
			m_score += s_scoresLevel3;
		}
		break;
		case 4:
		{
			m_score += s_scoresLevel4;
		}
		break;
	}

	if( m_linesLevel >= LINES_COUNT_LEVEL )
	{
		if( m_config->getSoundEffects() )
		{
			GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_LEVEL_UP ) );
		}

		m_level++;
		m_linesLevel -= LINES_COUNT_LEVEL;
	}

}

int Board::GetXPosInPixels( const int pos ) const
{
	return ( ( BOARD_POS_GAME_VALUES[ GetApp()->getResolutionType() ] - ( SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] * ( BOARD_WIDTH / 2 ) ) ) + ( pos * SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] ) );
}

int Board::GetYPosInPixels( const int pos ) const
{
	return ( ( m_screenHeight - ( SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] * BOARD_HEIGHT ) ) + ( pos * SCALE_GAME_VALUES[ GetApp()->getResolutionType() ] ) );
}