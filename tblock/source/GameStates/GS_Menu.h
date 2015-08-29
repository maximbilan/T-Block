#ifndef _GS_MAINMENU_H_
#define _GS_MAINMENU_H_

#include "GameState.h"

class Timer;

class GS_Menu : public GameState
{
	public:
		static const int k_substate_none = 0;
		static const int k_substate_splash_screen = 1;
		static const int k_substate_main = 2;

		Timer* m_timer;
		double m_startTime;
		float  m_alpha;

	public:
		GS_Menu();
		virtual ~GS_Menu();

		void ResumeState();
		void UpdateState( int frameTime );
		void RenderState();
};

#endif