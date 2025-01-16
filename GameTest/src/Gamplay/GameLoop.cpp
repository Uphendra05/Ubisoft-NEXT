#include "stdafx.h"
#include "GameLoop.h"

#include "src/System/MovementSystem.h"
#include "src/System/RenderSystem.h"
#include "src/System/PlayerMovement.h"
#include "src/System/Debug/CollisionSystem.h"
#include "src/System/CameraSystem.h"
#include "src/System/UI/WorldUI.h"
#include "src/System/RaycastSystem.h"
#include "src/System/FrameSystem.h"

void Engine::GameLoop::Start(CScene* pScene)
{
	systemFactory.CreateSystems<PlayerMovement>();
	systemFactory.CreateSystems<MovementSystem>();
	systemFactory.CreateSystems<RenderSystem>();
	//systemFactory.CreateSystems<CameraSystem>();
	systemFactory.CreateSystems<WorldUI>();
	systemFactory.CreateSystems<CollisionSystem>();
	systemFactory.CreateSystems<RaycastSystem>();
	systemFactory.CreateSystems<FrameSystem>();








	systemFactory.Start(pScene);
}

void Engine::GameLoop::Update(CScene* pScene, float deltaTime)
{
	systemFactory.Update(pScene, deltaTime);
}

void Engine::GameLoop::Render(CScene* pScene)
{
	systemFactory.Render(pScene);

}

void Engine::GameLoop::End(CScene* pScene)
{
	systemFactory.End(pScene);

}

void Engine::GameLoop::Cleanup()
{
	systemFactory.Cleanup();

}
