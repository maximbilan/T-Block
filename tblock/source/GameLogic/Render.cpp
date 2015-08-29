#include "PlatformPrecomp.h"
#include "Render.h"
#include "Board.h"
#include "GUI/GUI_MainMenu.h"
#include "Defines/GameConstants.h"

Render::Render()
{
	if( !m_surface.IsLoaded() )
	{
		char path[256];
		sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_ATLAS, RES_ID_NONE ).c_str(), s_textureUImenus );
		m_surface.LoadFile( path );
	}
}

Render::~Render()
{
}

void Render::DrawRectangle( const float pX1, const float pY1, const E_TYPE_COLOR color, const float scaleX, const float scaleY )
{
	//m_surf[ color ].Blit( pX1, pY1 );

	TextureImage* img = GetBaseApp()->getAtlasManager()->findImage( RES_TYPE_COLOR_ARRAY[ color ] );

	float imgX = static_cast<float>( img->getX() );
	float imgY = static_cast<float>( img->getY() );
	float imgWidth = static_cast<float>( img->getWidth() );
	float imgHeight = static_cast<float>( img->getHeight() );

	rtRectf r( pX1, pY1, pX1 + imgWidth, pY1 + imgHeight );
	r.Scale( ALIGNMENT_CENTER, CL_Vec2f( scaleX, scaleY ) );
	rtRectf s( imgX, imgY,  imgX + imgWidth , imgY + imgHeight );
	s.Scale( ALIGNMENT_CENTER, CL_Vec2f( scaleX, scaleY ) );

	m_surface.BlitEx( r, s );
}

void Render::RDrawLine( const float pX1, const float pY1, const float pX2, const float pY2 )
{
	DrawLine( MAKE_RGBA( 0,255,0,100 ), pX1, pY1, pX2, pY2 );
}