#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "GUI_InputBestScore.h"
#include "Entity/EntityUtils.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "Defines/GUI_IDs.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"

void InputBestScoreOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_INPUTBESTSCORE_BACK_BUTTON )
	{
		Tetris* tetris = Tetris::GetInstance();	
		Config* config = Config::GetInstance();

		GetApp()->buttonClickSound();

		std::string name;
		Entity* entityBox = GetEntityRoot()->GetEntityByName( GUI_TEXT_INPUTBESTSCORE_EDITBOX );
		if( entityBox )
		{
			name = entityBox->GetComponentByName( "InputTextRender" )->GetVar( "text" )->GetString();
		}
		if( strcmp( name.c_str(),"" ) == 0 )
		{
			name = config->getString( STR_IBS_TEST_NAME );
		}

		config->addNewScore( name, tetris->getScoreInt() );
		config->Save();
		tetris->ResetEndGame();

		config->FreeInstance();
		tetris->FreeInstance();

		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}

	
}

Entity* InputBestScoreCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_inputBestScoreMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &InputBestScoreOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}