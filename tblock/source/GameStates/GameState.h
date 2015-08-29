#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_

class GameState
{
	public:	
		// game states stack
		static const int k_statesStackLen = 10;

		GameState();
		virtual ~GameState();

		virtual void ResumeState() = 0;
		virtual void UpdateState( int frameTime ) = 0;
		virtual void RenderState() = 0;

		// static methods for states management
		static void InitStatesStack();	
		static void ReleaseStatesStack();
		static void SetState( GameState* newState );
		static void SetStateAndResetStack( GameState* newState );
		static void PopState();
		static void UpdateCurrentState( int frameTime );
		static void RenderCurrentState();
		static void SetSubState( const int state );
		static GameState* GetCurrentState();
	
	protected:

		// states management static vars
		static int			s_statesStackHead;
		static GameState*	s_statesStack[k_statesStackLen];
		static GameState*   s_currentState;
		static GameState*	s_stateToPop;
		static bool			s_resetStack;
		static int			s_subState;
};

#endif