#include "stdafx.h"
#include "GameLoop.h"

#include "src/System/MovementSystem.h"
#include "src/System/RenderSystem.h"
#include "src/System/PlayerMovement.h"
#include "src/System/CollisionSystem.h"
#include "src/System/CameraSystem.h"
#include "src/System/WorldUISystem.h"
#include "src/System/RaycastSystem.h"
#include "src/System/FrameSystem.h"
#include "src/System/PlayerHealthSystem.h"

void Engine::GameLoop::Start(CScene* pScene)
{
	systemFactory.CreateSystems<PlayerMovement>();
	systemFactory.CreateSystems<MovementSystem>();
	systemFactory.CreateSystems<RenderSystem>();
	systemFactory.CreateSystems<WorldUISystem>();
	systemFactory.CreateSystems<RaycastSystem>();
	systemFactory.CreateSystems<FrameSystem>();
	systemFactory.CreateSystems<PlayerHealthSystem>();
	systemFactory.CreateSystems<CollisionSystem>();








	//systemFactory.CreateSystems<CameraSystem>();
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
