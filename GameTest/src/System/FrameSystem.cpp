#include "stdafx.h"
#include "FrameSystem.h"
#include "src/Utilities/ComponentUtils.h"

const float POSITIONX = 750.0f;
const float POSITIONY = 700.0f;
std::string FRAMETEXT = "  ";
const float COLOR[3] = { 1.0f, 1.0f, 1.0f };

std::string Engine::FrameSystem::SystemName()
{
    return std::string();
}

void Engine::FrameSystem::Init()
{
}

void Engine::FrameSystem::Start(CScene* pScene)
{
	FrameCounterComponent* mFrameCounter = ComponentUtils::GetFrameCounter();
    mFrameCounter->frameCount = 0;
    mFrameCounter->fpsTimer = 0;
}

void Engine::FrameSystem::Update(CScene* pScene, float deltaTime)
{
	deltaTime = deltaTime / 1000.0f;
	FrameCounterComponent* mFrameCounter = ComponentUtils::GetFrameCounter();
	mFrameCounter->frameCount++;
	mFrameCounter->fpsTimer += deltaTime;

	// keeping track of FPS
	if (mFrameCounter->fpsTimer >= 1.0f)
	{
		mFrameCounter->fps = (float)(mFrameCounter->frameCount) / mFrameCounter->fpsTimer;

		mFrameCounter->frameCount = 0;
		mFrameCounter->fpsTimer = 0.0f;
		FRAMETEXT = "Frames :" + std::to_string(mFrameCounter->fps);
	}
}

void Engine::FrameSystem::Render(CScene* pScene)
{
	//App::Print(POSITIONX, POSITIONY, FRAMETEXT.c_str(), COLOR[0], COLOR[1], COLOR[2]);

}

void Engine::FrameSystem::End(CScene* pScene)
{
}

void Engine::FrameSystem::Cleanup()
{
}
