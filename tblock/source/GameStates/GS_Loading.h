#ifndef _GS_LOADING_H_
#define _GS_LOADING_H_

#include "GameState.h"

class GS_Loading : public GameState
{
	private:

	public:
		GS_Loading();
		virtual ~GS_Loading();

		void ResumeState();
		void UpdateState( int frameTime );
		void RenderState();

		void OnRender( VariantList *pVList );
		void OnUpdate( VariantList *pVList );
		void OnInput( VariantList *pVList );
};

#endif