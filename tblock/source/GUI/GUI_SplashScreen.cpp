#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "GUI_SplashScreen.h"
#include "Entity/EntityUtils.h"
#include "Entity/SplashComponent.h"
#include "Defines/GameConstants.h"
#include "Defines/GUI_IDs.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"

void SplashScreenOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	if (pEntClicked->GetName() == GUI_IMAGEBUTTON_SPLASH_SCREEN_BUTTON )
	{
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}
}

void SplashScreenOnUpdate( VariantList* pVList )
{

}

Entity* SplashScreenCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_splash_screen );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_splashScreenMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &SplashScreenOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	config->FreeInstance();

	FadeInEntity( pBG, true, 1000 );

	return pBG;
}
