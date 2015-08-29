#ifndef _RENDER_H_
#define _RENDER_H_

#include "Defines/GameIDS.h"

class Render
{
	private:
		Surface m_surf[8];
		Surface m_surface;

	public:

		Render();
		~Render();

		void DrawRectangle( const float pX1, const float pY1, const E_TYPE_COLOR color, const float scaleX = 1.0f, const float scaleY = 1.0f );
		void RDrawLine( const float pX1, const float pY1, const float pX2, const float pY2 );
};



#endif