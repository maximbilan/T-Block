#pragma once

#include "BaseApp.h"
#include "GameLogic/Tetris.h"
#include "Config/Config.h"
#include "Defines/DVideoModes.h"
#include "Utils/Resource.h"

class App: public BaseApp
{
public:
	
	App();
	virtual ~App();
	
	virtual bool Init();
	virtual void Kill();
	virtual void Draw();
	virtual void OnScreenSizeChange();
	virtual void Update();

	string GetVersionString();
	float GetVersion();
	int GetBuild();
	void GetServerInfo( string &server, uint32 &port );
	VariantDB* GetShared(){return &m_varDB;}
	Variant* GetVar(const string &keyName );
	Variant* GetVarWithDefault(const string &varName, const Variant &var) {return m_varDB.GetVarWithDefault(varName, var);}
	int GetSpecial();
	
	void OnUpdate( VariantList *pVList );
	void OnRender( VariantList *pVList );
	void OnInput( VariantList *pVList );
	virtual void OnEnterBackground();
	virtual void OnEnterForeground();
	void OnExitApp(VariantList *pVarList);

	bool isGame();
	void setGame(bool value);

	void buttonClickSound();
	bool isContinue();
	void setContinueBtn(bool value);
	E_RESOLUTION_TYPE getResolutionType();

	Resource* getResourceInstance();

private:

	void SaveStuff();

	bool m_bDidPostInit;
	VariantDB m_varDB;
	int m_special;

	bool m_isGame;
	Tetris* m_tetris;
	Config* m_config;

	E_RESOLUTION_TYPE rt_type;

	Surface m_surf;

	bool continueBtn;
	Resource* resource;

};

App* GetApp();
const char* GetBundlePrefix();
const char* GetBundleName();