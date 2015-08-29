#ifndef _GAME_H_
#define _GAME_H_

#include "Board.h"
#include "Figure.h"
#include <time.h>
#include "Render.h"
#include "Defines/GameIDS.h"

//#define WAIT_TIME 3000			// Number of milliseconds that the piece remains before going 1 block down */ 

class Game
{
	private:

		int m_screenHeight;					// Screen height in pixels
		int m_nextPosX, m_nextPosY;			// Position of the next piece
		int m_nextFigure, m_nextRotation;	// Kind and rotation of the next piece
		E_TYPE_COLOR m_nextColor;

		Render* m_io;
		Board*  m_board;
		Figure* m_figures;

		int m_posX, m_posY;				// Position of the piece that is falling down
		int m_figure, m_rotation;		// Kind and rotation the piece that is falling down
		E_TYPE_COLOR m_color;

		int GetRand( const int a, const int b );
		void InitGame();
		void DrawPiece( const int x, const int y, const int figure, const int rotation, const E_TYPE_COLOR color, bool nextFigure = false );

	public:
		Game();
		Game( Board *board, Figure *figures, Render *io, int screenHeight );
		~Game();

		void DrawScene();
		void DrawGameOver();
		void CreateNewPiece();

		void DrawBoard();
		void Reset();
		void ResetBoard();

		int getPosX() const;
		int getPosY() const;
		int getFigure() const;
		int getRotation() const;
		E_TYPE_COLOR getColor() const;

		void setPosX( const int value );
		void setPosY( const int value );
		void setFigure( const int value );
		void setRotation( const int value );
		void setColor( const E_TYPE_COLOR value );
};

inline int Game::getPosX() const
{
	return m_posX;
}

inline int Game::getPosY() const
{
	return m_posY;
}

inline int Game::getFigure() const
{
	return m_figure;
}

inline int Game::getRotation() const
{
	return m_rotation;
}

inline E_TYPE_COLOR Game::getColor() const
{
	return m_color;
}

inline void Game::setPosX( const int value )
{
	m_posX = value;
}

inline void Game::setPosY( const int value )
{
	m_posY = value;
}

inline void Game::setFigure( const int value )
{
	m_figure = value;
}

inline void Game::setRotation( const int value )
{
	m_rotation = value;
}

inline void Game::setColor( const E_TYPE_COLOR value )
{
	m_color = value;
}

#endif