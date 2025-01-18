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

#include "src/Utilities/GamplayUtils.h"
#include "src/ECS/CScene.h"
#include "src/Gamplay/GameLoop.h"

//------------------------------------------------------------------------
#include "app\app.h"
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Example data....
//------------------------------------------------------------------------


void CreateExamplePlayer();
void UpdateExamplePlayer(float dt);
void RenderExamplePlayer();
void ShutdownExamplePlayer();



 

enum
{
	ANIM_FORWARDS,
	ANIM_BACKWARDS,
	ANIM_LEFT,
	ANIM_RIGHT,
};
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
using namespace Engine;

CScene* scene = new CScene();
GameLoop mainGame;
void Init()
{


	//Vector2Tests::RunAllTests();
	
	
	GamplayUtils::CreateBackground(scene, Vector2(510,385));

	GamplayUtils::CreatePlayer(scene, Vector2(400.0f, 400.0f));


	GamplayUtils::CreateCollidable(scene, Vector2(200.0f, 200.0f));


	//GamplayUtils::CreateCollidable2(scene, Vector2(400.0f, 200.0f));

	GamplayUtils::CreateCamera(scene, Vector2(400.0f, 400.0f));

	mainGame.Start(scene);
	
	

	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	//test->Update(scene, speed);
	//------------------------------------------------------------------------
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(const float deltaTime)
{

	


	//------------------------------------------------------------------------
	// Example Sprite Code....

	mainGame.Update(scene, deltaTime);
	scene->DestroyEntities();
	//UpdateExamplePlayer(deltaTime);

	
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine,Print, DrawSprite.) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	mainGame.Render(scene);

	

	//RenderExampleP\layer();
	//------------------------------------------------------------------------

	//------------------------------------------------------------------------
	// Example Text.
	//------------------------------------------------------------------------
	

	//------------------------------------------------------------------------
	// Example Line Drawing.
	//------------------------------------------------------------------------
	
}
//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{	
	//------------------------------------------------------------------------
	// Example Sprite Code....
	
	//ShutdownExamplePlayer();

	mainGame.Cleanup();

	delete scene;
	//------------------------------------------------------------------------
}




CSimpleSprite *testSprite;
void CreateExamplePlayer()
{
	testSprite = App::CreateSprite(".\\TestData\\Test.bmp", 8, 4);
	testSprite->SetPosition(400.0f, 400.0f);
	const float speed = 1.0f / 15.0f;
	testSprite->CreateAnimation(ANIM_BACKWARDS, speed, { 0,1,2,3,4,5,6,7 });
	testSprite->CreateAnimation(ANIM_LEFT, speed, { 8,9,10,11,12,13,14,15 });
	testSprite->CreateAnimation(ANIM_RIGHT, speed, { 16,17,18,19,20,21,22,23 });
	testSprite->CreateAnimation(ANIM_FORWARDS, speed, { 24,25,26,27,28,29,30,31 });
	testSprite->SetScale(1.0f);

}

void UpdateExamplePlayer(float dt)
{
	testSprite->Update(dt);
	if (App::GetController().GetLeftThumbStickX() > 0.5f)
	{
		testSprite->SetAnimation(ANIM_RIGHT);
		float x, y;
		testSprite->GetPosition(x, y);
		x += 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().GetLeftThumbStickX() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_LEFT);
		float x, y;
		testSprite->GetPosition(x, y);
		x -= 1.0f;
		testSprite->SetPosition(x, y);
	}
    if (App::GetController().GetLeftThumbStickY() > 0.5f)
    {
        testSprite->SetAnimation(ANIM_FORWARDS);
        float x, y;
        testSprite->GetPosition(x, y);
        y += 1.0f;
        testSprite->SetPosition(x, y);
    }
	if (App::GetController().GetLeftThumbStickY() < -0.5f)
	{
		testSprite->SetAnimation(ANIM_BACKWARDS);
		float x, y;
		testSprite->GetPosition(x, y);
		y -= 1.0f;
		testSprite->SetPosition(x, y);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_UP, false))
	{
		testSprite->SetScale(testSprite->GetScale() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_DOWN, false))
	{
		testSprite->SetScale(testSprite->GetScale() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_LEFT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() + 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_DPAD_RIGHT, false))
	{
		testSprite->SetAngle(testSprite->GetAngle() - 0.1f);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true))
	{
		testSprite->SetAnimation(-1);
	}
	//------------------------------------------------------------------------
	// Sample Sound.
	//------------------------------------------------------------------------
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true))
	{
		App::PlaySound(".\\TestData\\Test.wav", true);
	}
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_X, true))
	{
		App::StopSound(".\\TestData\\Test.wav");
	}
}

void RenderExamplePlayer()
{

	testSprite->Draw();
	App::Print(100, 100, "Sample Text");

	static float a = 0.0f;
	const float r = 1.0f;
	float g = 1.0f;
	float b = 1.0f;
	a += 0.1f;
	for (int i = 0; i < 20; i++)
	{

		const float sx = 200 + sinf(a + i * 0.1f) * 60.0f;
		const float sy = 200 + cosf(a + i * 0.1f) * 60.0f;
		const float ex = 700 - sinf(a + i * 0.1f) * 60.0f;
		const float ey = 700 - cosf(a + i * 0.1f) * 60.0f;
		g = (float)i / 20.0f;
		b = (float)i / 20.0f;
		App::DrawLine(sx, sy, ex, ey, r, g, b);
	}
}

void ShutdownExamplePlayer()
{
	delete testSprite;
}


