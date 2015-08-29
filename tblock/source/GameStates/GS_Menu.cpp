#include "PlatformPrecomp.h"
#include "GS_Menu.h"
#include "Defines/GUI_IDs.h"
#include "GUI/GUI_MainMenu.h"
#include "Utils/Timer.h"

GS_Menu::GS_Menu() :
	m_timer( new Timer() ),
	m_startTime( 0.0f ),
	m_alpha( 1.0f )
{
	m_timer->start();
	m_startTime = m_timer->getElapsedTimeInMilliSec();
}

GS_Menu::~GS_Menu()
{
	delete m_timer;
}

void GS_Menu::ResumeState()
{
}

void GS_Menu::UpdateState( int frameTime )
{
	switch( s_subState )
	{
		case k_substate_splash_screen:
		{
			Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_TEXT_SPLASH_SCREEN_TEXT_ );
			if( pEnt )
			{
				if( m_timer->getElapsedTimeInMilliSec() - m_startTime > 2000.0f )
				{
					m_startTime = m_timer->getElapsedTimeInMilliSec();
					m_alpha = 1.0f;
				}
				else
				{
					if( m_alpha > 0.0f )
					{
						m_alpha -= 0.01f;
					}
				}
				pEnt->GetVar( "alpha" )->Set( Variant( m_alpha ) );
			}

			pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGE_SPLASH_SCREEN_TITLE_T_BLOCK );
			if( pEnt )
			{
				pEnt->GetVar( "rotation" )->Set( Variant( SinGamePulseByMS(10000)*1 ) );
			}
		}
		break;

		case k_substate_main:
		{
			Entity* pEnt = GetEntityRoot()->GetEntityByName( GUI_IMAGE_MM_TITLE_T_BLOCK );
			if( pEnt )
			{
				pEnt->GetVar( "rotation" )->Set( Variant( SinGamePulseByMS(10000)*1 ) );
			}
		}
		break;
	}
}

void GS_Menu::RenderState()
{
	switch( s_subState )
	{
		case k_substate_splash_screen:
		{
		}
		break;

		case k_substate_main:
		{
		}
		break;
	}
}