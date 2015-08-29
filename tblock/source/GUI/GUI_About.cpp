#include "PlatformPrecomp.h"
#include "GUI_MainMenu.h"
#include "GUI_About.h"
#include "Entity/EntityUtils.h"
#include "Defines/LangIDS.h"
#include "Config/Config.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"
#include "Defines/GUI_IDs.h"

const float aboutMenuTextAreaPosX = 2;
const float aboutMenuTextAreaPosY = 10;
const float aboutMenuOffsetFromBottom = 42;
const float aboutMenuOffsetFromRight = 0;
const float aboutMenuStartX = 25;
const float aboutMenuStartY = 100;
const float aboutMenuSpacerY = 25;
const float aboutMenuWidth = 240;

void AboutOnSelect( VariantList* pVList )
{
	Entity* pEntClicked = pVList->m_variant[1].GetEntity();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_ABOUT_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		MainMenuCreate( pEntClicked->GetParent()->GetParent() );
	}
}

void AboutMenuAddScrollContent( Entity* pParent )
{
	Config* config = Config::GetInstance();

	pParent = pParent->GetEntityByName( "scroll_child" );
	pParent->RemoveAllEntities();		// clear it out in case we call this more than once, say, to update/change something

	float x = aboutMenuStartX; 
	float y = aboutMenuStartY;
	float spacerY = iPhoneMapY( aboutMenuSpacerY );		//space between thingies

	Entity* pText;

	string msg;

	msg = config->getString( (E_LANG_TYPE)STR_ABOUT_TITLE_HEADER );
	msg += "\n";
	pText = CreateTextLabelEntity( pParent, "TitleScores", iPhoneMapX( aboutMenuWidth ), y, msg );
	pText->GetVar( "alignment" )->Set( uint32( ALIGNMENT_CENTER ) );
	y += spacerY;
	msg = GetApp()->GetVersionString();
	msg += "\n\n";
	pText = CreateTextLabelEntity( pParent, "TitleScores", iPhoneMapX( aboutMenuWidth ), y, msg );
	pText->GetVar( "alignment" )->Set( uint32( ALIGNMENT_CENTER ) );
	y += spacerY;

	for( short int i = STR_ABOUT_TITLE_START; i <= STR_ABOUT_TITLE_END; i++ )
	{
		msg = config->getString( ( E_LANG_TYPE ) i );
		msg += "\n";
		pText = CreateTextLabelEntity( pParent, "TitleScores", iPhoneMapX( aboutMenuWidth ), y, msg );
		pText->GetVar( "alignment" )->Set( uint32( ALIGNMENT_CENTER ) );
		y += spacerY;
	}

	//automatically calculate the total size of this entity with all its children for the scroll bars, do this at the end
	VariantList vList( pParent->GetParent() );
	ResizeScrollBounds( &vList );

	config->FreeInstance();
}

Entity * AboutCreate( Entity *pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_aboutMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &AboutOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = pParentEnt->AddEntity( new Entity );

	std::string imgPath = GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_ATLAS, RES_ID_NONE ).c_str();
	CreateOverlayCustomEntity( pBG, "ui_background", "background", 0, 0, imgPath );

	//setup the dimensions of where the scroll area will go
	CL_Vec2f vTextAreaPos = iPhoneMap( aboutMenuTextAreaPosX, aboutMenuTextAreaPosY );
	float offsetFromBottom = iPhoneMapY( aboutMenuOffsetFromBottom );
	float offsetFromRight = iPhoneMapY( aboutMenuOffsetFromRight );

	CL_Vec2f vTextAreaBounds = ( GetScreenSize() - CL_Vec2f( offsetFromRight, offsetFromBottom ) ) - vTextAreaPos;
	Entity* pScroll = pBG->AddEntity( new Entity( "scroll" ) );
	pScroll->GetVar( "pos2d" )->Set( vTextAreaPos );
	pScroll->GetVar( "size2d" )->Set( vTextAreaBounds );
	pScroll->AddComponent( new TouchHandlerComponent );

	EntityComponent* pFilter = pScroll->AddComponent( new FilterInputComponent );
	EntityComponent* pScrollComp = pScroll->AddComponent( new ScrollComponent );
	
	//note: If you don't want to see a scroll bar progress indicator, comment out the next line.  Also note that it only draws
	//a vertical progress bar if needed but doesn't draw a horizontal if needed (I just haven't needed a horizontal scroll bar yet)
	EntityComponent* pScrollBarComp = pScroll->AddComponent( new ScrollBarRenderComponent );	//also let's add a visual way to see the scroller position
	Entity* pScrollChild = pScroll->AddEntity( new Entity( "scroll_child" ) );

	AboutMenuAddScrollContent( pBG );

	parser->createEntities( pBG );
	delete parser;

	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}