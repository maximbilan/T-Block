#ifndef _GS_GAMEPLAY_H_
#define _GS_GAMEPLAY_H_

#include "GameState.h"

class Tetris;
class Config;

class GS_GamePlay : public GameState
{
	private:
		Tetris* m_tetris;
		Config* m_config;

	public:
		GS_GamePlay();
		virtual ~GS_GamePlay();

		void ResumeState();
		void UpdateState( int frameTime );
		void RenderState();
};

#endif