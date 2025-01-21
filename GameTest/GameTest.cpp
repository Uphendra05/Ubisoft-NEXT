///////////////////////////////////////////////////////////////////////////////
// Filename: GameTest.cpp
// Provides a demo of how to use the API
///////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h>  
#include "src/UnitTests/Vector2Tests.h"
#include "src/UnitTests/ECSTest.h"

#include "src/ECS/CScene.h"
#include "src/Gamplay/GameLoop.h"

//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------


//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
using namespace Engine;

CScene* scene = new CScene();
GameLoop* mainGame = new GameLoop();

void Init()
{


	mainGame->Start(scene);

	
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{


	mainGame->Update(scene, deltaTime);
	scene->DestroyEntities();

}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	
	mainGame->Render(scene);

}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	
	mainGame->Cleanup();

	delete scene;
	delete mainGame;
}

