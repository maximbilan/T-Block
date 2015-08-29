#include "PlatformPrecomp.h"
#include "App.h"
#include "GUI/GUI_MainMenu.h"
#include "Entity/EntityUtils.h"
#include "FileSystem/FileSystemZip.h"
#include "Renderer/LinearParticle.h"
#include "GUI/GUI_InputBestScore.h"
#include "GUI/GUI_SplashScreen.h"
#include "Defines/LangIDS.h"
#include "Defines/GameConstants.h"
#include "GameStates/GameState.h"
#include "GameStates/GS_Menu.h"

MessageManager g_messageManager;
MessageManager* GetMessageManager()
{
	return &g_messageManager;
}

FileManager g_fileManager;
FileManager * GetFileManager()
{
	return &g_fileManager;
}

#ifdef __APPLE__

#if TARGET_OS_IPHONE == 1
	//it's an iPhone or iPad
	//#include "Audio/AudioManagerOS.h"
	//AudioManagerOS g_audioManager;
	#include "Audio/AudioManagerDenshion.h"
	
	AudioManagerDenshion g_audioManager;
#else
	//it's being compiled as a native OSX app
   #include "Audio/AudioManagerFMOD.h"
  AudioManagerFMOD g_audioManager; //dummy with no sound

//in theory, CocosDenshion should work for the Mac builds, but right now it seems to want a big chunk of
//Cocos2d included so I'm not fiddling with it for now

//#include "Audio/AudioManagerDenshion.h"
//AudioManagerDenshion g_audioManager;
#endif
	
#else

#if defined RT_WEBOS || defined RTLINUX
#include "Audio/AudioManagerSDL.h"
AudioManagerSDL g_audioManager; //sound in windows and WebOS
//AudioManager g_audioManager; //to disable sound
#elif defined ANDROID_NDK
#include "Audio/AudioManagerAndroid.h"
AudioManagerAndroid g_audioManager; //sound for android
#elif defined PLATFORM_BBX
#include "Audio/AudioManagerBBX.h"
//AudioManager g_audioManager; //to disable sound
AudioManagerBBX g_audioManager;
#elif defined PLATFORM_FLASH
//AudioManager g_audioManager; //to disable sound
#include "Audio/AudioManagerFlash.h"
AudioManagerFlash g_audioManager;
#else

//in windows
//AudioManager g_audioManager; //to disable sound

#ifdef RT_FLASH_TEST
#include "Audio/AudioManagerFlash.h"
AudioManagerFlash g_audioManager;
#else

#include "Audio/AudioManagerAudiere.h"
AudioManagerAudiere g_audioManager;  //Use Audiere for audio
#endif
//#include "Audio/AudioManagerFMOD.h"
//AudioManagerFMOD g_audioManager; //if we wanted FMOD sound in windows

#endif
#endif

AudioManager * GetAudioManager()
{
	return &g_audioManager;
}

App *g_pApp = NULL;
BaseApp * GetBaseApp() 
{
	if( !g_pApp )
	{
#ifndef NDEBUG
		LogMsg( "Creating app object" );
#endif
		g_pApp = new App;
	}

	return g_pApp;
}

App* GetApp()
{
	return g_pApp;
}

App::App()
{
	m_bDidPostInit = false;
	m_isGame = false;
}

App::~App()
{
	L_ParticleSystem::deinit();
}

bool App::Init()
{	
	SetDefaultButtonStyle( Button2DComponent::BUTTON_STYLE_CLICK_ON_TOUCH_RELEASE );
	//SetManualRotationMode( true );
	
    bool bScaleScreenActive = false; //if true, we'll stretch every screen to the coords below
    int scaleToX = 480;
	int scaleToY = 320;
    
	switch( GetEmulatedPlatformID() )
	{
		//special handling for certain platforms to tweak the video settings

		case PLATFORM_ID_WEBOS:
		{
			//if we do this, everything will be stretched/zoomed to fit the screen
			if( IsIPADSize )
			{
				//doesn't need rotation
				SetLockedLandscape( false );  //because it's set in the app manifest, we don't have to rotate ourselves
				SetupScreenInfo( GetPrimaryGLX(), GetPrimaryGLY(), ORIENTATION_PORTRAIT );
				if( bScaleScreenActive )
				{
	                SetupFakePrimaryScreenSize( scaleToX, scaleToY ); //game will think it's this size, and will be scaled up
				}
			} 
			else
			{
				//but the phones do
				SetLockedLandscape( true ); //we don't allow portrait mode for this game
				if( bScaleScreenActive )
				{
	                SetupFakePrimaryScreenSize( scaleToX, scaleToY ); //game will think it's this size, and will be scaled up
				}
			}
		}	
		break;

		case PLATFORM_ID_IOS:
		{
			SetLockedLandscape( false ); //we stay in portrait but manually rotate, gives better fps on older devices
            
			if( bScaleScreenActive )
			{
                SetupFakePrimaryScreenSize( scaleToX, scaleToY ); //game will think it's this size, and will be scaled up
			}
		}
		break;
			
		default:
		{
			//Default settings for other platforms

			SetLockedLandscape( false ); //we don't allow portrait mode for this game
			SetupScreenInfo(GetPrimaryGLX(), GetPrimaryGLY(), ORIENTATION_PORTRAIT);
	        if( bScaleScreenActive )
			{
				SetupFakePrimaryScreenSize( scaleToX, scaleToY ); //game will think it's this size, and will be scaled up
			}
		}
	}

	L_ParticleSystem::init( 2000 );

	if( m_bInitted )	
	{
		return true;
	}
	
	if( !BaseApp::Init() )
	{
		return false;
	}

	LogMsg("Save path is %s", GetSavePath().c_str());

	continueBtn = false;

	const int screenX = GetPrimaryGLX();
	const int screenY = GetPrimaryGLY();
	
	if( ( screenX == 320 ) && ( screenY == 480 ) )
	{
		rt_type = RT_320_480;
	}
	else if( ( screenX == 480) && ( screenY == 320 ) )
	{
		rt_type = RT_320_480;
	}
	else if( ( screenX == 480 ) && ( screenY == 800 ) )
	{
		rt_type = RT_480_800;
	}
	else if( ( screenX == 480 ) && ( screenY == 854 ) )
	{
		rt_type = RT_480_854;
	}
	else if( ( ( screenX == 600 ) && ( screenY == 1024 ) ) || (( screenX == 1024 ) && ( screenY == 600 ) ) )
	{
		rt_type = RT_600_1024;
	}
	else if( ( ( screenX == 768 ) && ( screenY == 1024 ) ) || ( ( screenX == 1024 ) && ( screenY == 768 ) ) )
	{
		rt_type = RT_768_1024;
	}
	else if( ( screenX == 540 ) && ( screenY == 960 ) )
	{
		rt_type = RT_480_800;
	}
	else if( ( ( screenX == 640 ) && ( screenY == 960 ) ) || ( ( screenY == 640 ) && ( screenX == 960 ) ) )
	{
		rt_type = RT_640_960;
	}
	else if( ( ( screenX == 640 ) && ( screenY == 1136 ) ) || ( ( screenY == 640 ) && ( screenX == 1136 ) ) )
	{
		rt_type = RT_640_1136;
	}
	else if( ( ( screenX == 768 * 2 ) && ( screenY == 1024 * 2 ) ) || ( ( screenY == 768 * 2 ) && ( screenX == 1024 * 2 ) ) )
	{
		rt_type = RT_768_1024;
		SetupFakePrimaryScreenSize( 768, 1024 );
	}
	else if( ( screenX == 720 ) && ( screenY == 1280 ) )
	{
		rt_type = RT_720_1280;
	}
	else if( ( screenX == 1280 ) && ( screenY == 720 ) )
	{
		rt_type = RT_720_1280;
	}
	else if( ( screenX == 800 ) && ( screenY == 1280 ) )
	{
		rt_type = RT_800_1280;
	}
	else if( ( screenX == 1280 ) && ( screenY == 800 ) )
	{
		rt_type = RT_800_1280;
	}
	else if( ( screenX == 768 ) && ( screenY == 1280 ) )
	{
		rt_type = RT_768_1280;
	}
	else if( ( screenX == 1280 ) && ( screenY == 768 ) )
	{
		rt_type = RT_768_1280;
	}
	else
	{
		rt_type = RT_480_800;
	}

	//preload audio
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_BTN_CLICK));
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_ERASE_LINE));
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_FIGURE_DOWN));
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_FIGURE_MOVE));
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_LEVEL_UP));
	GetAudioManager()->Preload(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_GAME_OVER));
	//GetAudioManager()->Preload( GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_THEME ) );
	
	m_config = Config::GetInstance();
	m_config->Init();

	m_tetris = Tetris::GetInstance();
	m_tetris->Init();
	
	resource = new Resource();
	
	if( GetFileManager()->FileExists( GetSavePath() + "Config.cfg" ) )
	{
		LogMsg( "go to loading config" );
		m_config->Load();
	}
	else
	{
		LogMsg( "go to resetting config" );
		m_config->ResetToDefault();
		m_config->Save();
	}
	
	char path[256];
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_SPRITE, RES_ID_NONE ).c_str(), s_spriteUIbackground );
	getAtlasManager()->loadAtlas( path );
	sprintf( path, "%s%s", GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_SPRITE, RES_ID_NONE ).c_str(), s_spriteUImenus );
	getAtlasManager()->loadAtlas( path );

	m_atlasManager->generateAtlasMap();

	if (!GetFont(FONT_SMALL)->Load(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_FONT, RES_ID_FONT_TAHOMA))) return false;
	if (!GetFont(FONT_LARGE)->Load(GetApp()->getResourceInstance()->getItem(GetApp()->getResolutionType(), RES_TYPE_FONT, RES_ID_FONT_TAHOMA))) return false;

	GameState::InitStatesStack();

	return true;
}

void App::Kill()
{
	GameState::ReleaseStatesStack();
	delete (Resource*) resource;
	m_tetris->Delete();
	m_tetris->FreeInstance();
	m_config->Remove();
	m_config->FreeInstance();
	BaseApp::Kill();
}

void App::Update()
{
	BaseApp::Update();

	if( !m_bDidPostInit )
	{
		m_bDidPostInit = true;
		m_special = GetSystemData() != C_PIRATED_NO;
		
		GameState::SetState( new GS_Menu() );

		Entity* pGUIEnt = GetEntityRoot()->AddEntity( new Entity( "GUI" ) );
		SplashScreenCreate( pGUIEnt );
		PreloadKeyboard();
	}
	else
	{
		GameState::UpdateCurrentState( 60 );
	}
}

void App::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	SetupOrtho();

	BaseApp::Draw();
	PrepareForGL();

	GameState::RenderCurrentState();
	
}

void App::OnScreenSizeChange()
{
	BaseApp::OnScreenSizeChange();
}

void App::OnUpdate( VariantList *pVList )
{
}

void App::OnRender( VariantList *pVList )
{
}

void App::OnInput( VariantList *pVList )
{
}

void App::GetServerInfo( string &server, uint32 &port )
{
#if defined (_DEBUG) && defined(WIN32)
	server = "localhost";
	port = 8080;

	//server = "www.rtsoft.com";
	//port = 80;
#else

	server = "rtsoft.com";
	port = 80;
#endif
}

int App::GetSpecial()
{
	return m_special; //1 means pirated copy
}

Variant * App::GetVar( const string &keyName )
{
	return GetShared()->GetVar(keyName);
}

std::string App::GetVersionString()
{
	return "1.1.0b";
}

float App::GetVersion()
{
	return 1.10f;
}

int App::GetBuild()
{
	return 1;
}

void App::SaveStuff()
{
	m_varDB.Save( "save.dat" );
}

void App::OnEnterBackground()
{
	SaveStuff();
	BaseApp::OnEnterBackground();
}

void App::OnEnterForeground()
{
	BaseApp::OnEnterForeground();
}


void App::OnExitApp(VariantList *pVarList)
{
	LogMsg("Exiting the app");

	OSMessage o;
	o.m_type = OSMessage::MESSAGE_FINISH_APP;
	GetBaseApp()->AddOSMessage(o);
}


void App::setGame( bool value )
{
	m_isGame = value;
}

bool App::isGame()
{
	return m_isGame;
}

bool App::isContinue()
{
	return continueBtn;
}

void App::setContinueBtn( bool value )
{
	continueBtn = value;
}

E_RESOLUTION_TYPE App::getResolutionType()
{
	return rt_type;
}

Resource* App::getResourceInstance()
{
	return resource;
}

void App::buttonClickSound()
{
	if( m_config->getSoundEffects() )
	{
		GetAudioManager()->Play( GetApp()->getResourceInstance()->getItem( GetApp()->getResolutionType(), RES_TYPE_AUDIO, RES_ID_AUDIO_BTN_CLICK ) );
	}
}

const char* GetAppName()
{
	return "tBlock";
};

//for palm webos, android, App Store
const char* GetBundlePrefix()
{
	const char * bundlePrefix = "com.maximbilan.";
	return bundlePrefix;
}

//applicable to Palm WebOS builds only
const char* GetBundleName()
{
	const char* bundleName = "tblock";
	return bundleName;
}
