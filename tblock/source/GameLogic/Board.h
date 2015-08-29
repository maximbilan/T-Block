#ifndef _BOARD_H_
#define _BOARD_H_

#include "Figure.h"
#include "Defines/GameIDS.h"

#define BOARD_LINE_WIDTH 2				// Width of each of the two lines that delimit the board
#define BLOCK_SIZE 20				    // Width and Height of each block of a piece
#define BOARD_POSITION 115				// Center position of the board from the left of the screen
#define BOARD_WIDTH 10			 	    // Board width in blocks 
#define BOARD_HEIGHT 20				    // Board height in blocks
#define MIN_VERTICAL_MARGIN 3			// Minimum vertical margin for the board limit 		
#define MIN_HORIZONTAL_MARGIN 3			// Minimum horizontal margin for the board limit
#define FIGURE_BLOCKS 5				    // Number of horizontal and vertical blocks of a matrix piece
#define LINES_COUNT_LEVEL 30			// Number of lines for next level

// Block type
enum
{ 
	BLOCK_FREE, 
	BLOCK_FILLED
};

class Config;

class Board
{
	private:

		Config* m_config;

		int m_board[BOARD_WIDTH][BOARD_HEIGHT]; 				// Board that contains the pieces
		E_TYPE_COLOR m_boardColor[BOARD_WIDTH][BOARD_HEIGHT];
		Figure* m_figures;
		int m_screenHeight;
		
		void DeleteLine( const int y );

		// Counters
		short int m_level;			// Level
		short int m_curLines;		// Lines for current event
		int       m_lines;			// Total number of lines
		short int m_linesLevel;		// Number of lines for next level
		long int  m_score;			// Score

	public:
		Board();
		Board( Figure *figures, int screenHeight );
		~Board();

		int GetXPosInPixels( const int pos ) const;
		int GetYPosInPixels( const int pos ) const;
		bool IsFreeBlock( const int x, const int y );
		bool IsPossibleMovement( const int x, const int y, const int figure, const int rotation );
		void StoreFigure( const int x, const int y, const int figure, const int rotation, const E_TYPE_COLOR color );
		void DeletePossibleLines();
		bool IsGameOver();
		void Reset();
		void InitBoard();

		short int getLevel() const;
		int getLines() const;
		long int getScore() const;
		E_TYPE_COLOR getColor( const short int i, const short int j ) const;
};

inline bool Board::IsGameOver()
{
	// If the first line has blocks, then, game over
	for( int i = 0; i < BOARD_WIDTH; i++ )
	{
		if( ( m_board[i][0] == BLOCK_FILLED ) || ( m_board[i][1] == BLOCK_FILLED ) )
		{
			return true;
		}
	}

	return false;
}

inline short int Board::getLevel() const
{
	return m_level;
}

inline int Board::getLines() const
{
	return m_lines;
}

inline long int Board::getScore() const
{
	return m_score;
}

inline E_TYPE_COLOR Board::getColor( const short int i, const short int j ) const
{
	return m_boardColor[i][j];
}

#endif