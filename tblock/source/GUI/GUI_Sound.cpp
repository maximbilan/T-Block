#include "PlatformPrecomp.h"
#include "GUI_Options.h"
#include "GUI_Sound.h"
#include "Entity/EntityUtils.h"
#include "Config/Config.h"
#include "Defines/Langs.h"
#include <string>
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "XMLMenu/XMLMenu.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"
#include "Defines/GUI_IDs.h"

void SoundOnSelect( VariantList* pVList )
{
	Entity *pEntClicked = pVList->m_variant[1].GetEntity();

	Config* config = Config::GetInstance();

	if( pEntClicked->GetName() == GUI_IMAGEBUTTON_SOUND_BACK_BUTTON )
	{
		GetApp()->buttonClickSound();
		SlideScreen( pEntClicked->GetParent(), false );
		GetMessageManager()->CallEntityFunction( pEntClicked->GetParent(), 500, "OnDelete", NULL );
		OptionsCreate( pEntClicked->GetParent()->GetParent() );
	}

	if( pEntClicked->GetName() == GUI_CHECKBOX_CHECKBOX_EFFECTS )
	{
		GetApp()->buttonClickSound();
		config->setSoundEffects( !config->getSoundEffects() );
		GetApp()->GetVar( "SoundEffects" )->Set( uint32(config->getSoundEffects() ) );
		config->Save();
	}

	if( pEntClicked->GetName() == GUI_CHECKBOX_CHECKBOX_MUSIC )
	{
		GetApp()->buttonClickSound();
		config->setMusic( !config->getMusic() );
		GetApp()->GetVar( "Music" )->Set( uint32( config->getMusic() ) );
		config->Save();
	}

	if( pEntClicked->GetName() == GUI_CHECKBOX_CHECKBOX_VIBRATION )
	{
		GetApp()->buttonClickSound();
		config->setVibration( !config->getVibration() );
		GetApp()->GetVar( "Vibration" )->Set( uint32( config->getVibration() ) );
		config->Save();

		if( config->getVibration() )
		{
			GetAudioManager()->Vibrate();
		}
	}

	config->FreeInstance();
}

Entity* SoundCreate( Entity* pParentEnt )
{
	GameState::GetCurrentState()->SetSubState( GS_Menu::k_substate_none );

	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_MENU, RES_ID_NONE ).c_str(), s_soundMenuXml );

	Config* config = Config::GetInstance();

	XMLMenu* parser = new XMLMenu( path, pParentEnt, &SoundOnSelect, config->getLangPack() );
	parser->Read();
	Entity* pBG = parser->createEntities();
	delete parser;

	std::string cbEffects = GUI_CHECKBOX_CHECKBOX_EFFECTS;
	std::string cbMusic = GUI_CHECKBOX_CHECKBOX_MUSIC;
	std::string cbVibration = GUI_CHECKBOX_CHECKBOX_VIBRATION;
		
	Entity *pEnt = GetEntityRoot()->GetEntityByName( cbEffects );
	if( pEnt )
	{
		SetCheckBoxChecked( pEnt, !config->getSoundEffects(), false );
		pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	
	pEnt = GetEntityRoot()->GetEntityByName( cbMusic );
	if( pEnt )
	{
		SetCheckBoxChecked( pEnt, !config->getMusic(), false );
		pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	
	pEnt = GetEntityRoot()->GetEntityByName( cbVibration );
	if( pEnt )
	{
		SetCheckBoxChecked( pEnt, !config->getVibration(), false );
		pEnt->GetComponentByName( "Button2D" )->GetVar( "repeatDelayMS" )->Set( uint32( 0 ) );
	}
	
	FadeInEntity( pBG, true, 1000 );

	config->FreeInstance();

	return pBG;
}