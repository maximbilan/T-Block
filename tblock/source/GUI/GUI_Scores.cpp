#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "GUI_Scores.h"
#include "Entity/EntityUtils.h"
#include "Config/Config.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "Defines/GUI_IDs.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"

const float scoresStartX = 40.0f;
const float scoresStartY = 50.0f;
const float scoresSpacerYhighRes = 55.0f;
const float scoresSpacerYlowRes = 30.0f;
const float scoresHighResLimit = 600.0f;
const float scoresTitleStartX = 150.0f;
const int scoresLinesCountHighRes = 10;
const int scoresLinesCountLowRes = 5;

void ScoresOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_SCORES_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}
}

Entity* ScoresCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_scoresMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &ScoresOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	scores_t scores = config->getScores();

	float x = scoresStartX;
	float y = scoresStartY;
	float y_spacer;

	if( GetPrimaryGLY() >= scoresHighResLimit )
	{
		y_spacer = scoresSpacerYhighRes;
	}
	else
	{
		y_spacer = scoresSpacerYlowRes;
	}

	Entity* pText;
	y += y_spacer;

	short int counter = 0;
	for( scores_t::const_iterator it = scores.begin(); it != scores.end(); ++it )
	{
		counter++;
		pText = CreateTextLabelEntity( pBG, "Titles", iPhoneMapX(x), y, ( *it ).second ); 
		pText->GetVar( "alignment" )->Set( uint32( ALIGNMENT_UPPER_LEFT ) );

		char string[256] = {0};
		sprintf( string, "%ld", ( *it ).first );
		pText = CreateTextLabelEntity( pBG, "Titles", GetPrimaryGLX()-iPhoneMapX( scoresTitleStartX ), y, string ); 

		pText->GetVar( "alignment" )->Set( uint32( ALIGNMENT_UPPER_LEFT ) );
		y += y_spacer;

		if( ( ( GetApp()->getResolutionType() == RT_240_320 ) || ( GetApp()->getResolutionType() == RT_1024_600 ) ) && ( counter == scoresLinesCountLowRes ) )
		{
			break;
		}

		if( ( GetEmulatedPlatformID() == PLATFORM_ID_ANDROID ) && ( counter == scoresLinesCountHighRes ) )
		{
			break;
		}

	}

	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}