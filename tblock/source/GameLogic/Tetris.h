#ifndef _TETRIS_H_
#define _TETRIS_H_

#include "Render.h"
#include "Board.h"
#include "Figure.h"
#include "Game.h"

#include "../Interface/Singleton.h"
#include "../Utils/Timer.h"

#if !defined(WAIT_TIME)
#define WAIT_TIME 700	// Number of milliseconds that the piece remains before going 1 block down */ 
#endif

// #define TET_SCREEN_HEIGHT 570
#define TET_SCREEN_HEIGHT 405

class Config;

class Tetris : public Singleton<Tetris>
{
	protected:

		Tetris() {}
		friend class Singleton<Tetris>;

		// Render
		Render* m_io;
		// Pieces
		Figure* m_figures;
		// Board
		Board* m_board;
		// Game
		Game* m_game;

		Config* m_config;

		Timer* m_timer;
		double m_tick1, m_tick2;

		bool m_endGame;

	public:

		void Init();
		void Reset();
		void Run();
		void Delete();

		void ClickLeft();
		void ClickRight();
		void ClickRotate();
		void ClickDown();
		void ClickForceDown();

		std::string getLevel() const;
		std::string getScore() const;
		std::string getLines() const;
		long int getScoreInt() const;

		bool isEndGame() const;
		void ResetEndGame();

};

inline std::string Tetris::getLevel() const
{
	char string[12] = {0};
	sprintf( string, "%d", m_board->getLevel() );
	
	return std::string( string );
}

inline std::string Tetris::getScore() const
{
	char string[12] = {0};
	sprintf( string, "%d", m_board->getScore() );
	
	return std::string( string );
}

inline std::string Tetris::getLines() const
{
	char string[12] = {0};
	sprintf( string, "%d", m_board->getLines() );
	
	return std::string( string );
}

inline bool Tetris::isEndGame() const
{
	return m_endGame;
}

inline void Tetris::ResetEndGame()
{
	m_endGame = false;
}

inline long int Tetris::getScoreInt() const
{
	return m_board->getScore();
}

#endif