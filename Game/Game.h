#pragma once

#include "GEApp.h"
#include "Singleton.h"

#define	GAME	    CGame::GetInstance()

class CGame : 
	public CGEApp, 
	public Singleton<CGame>
{
public:
	void			Init();
	void			Release();

};