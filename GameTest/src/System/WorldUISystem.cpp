#include "stdafx.h"
#include "WorldUISystem.h"

const float POSITIONX = 200.0f;
const float POSITIONY = 500.0f;
std::string UITEXT = " PRESS WASD TO MOVE ENTITY";
const float COLOR[3] = { 1.0f, 1.0f, 1.0f };


std::string Engine::WorldUISystem::SystemName()
{
    return std::string();
}

void Engine::WorldUISystem::Init()
{
}

void Engine::WorldUISystem::Start(CScene* pScene)
{
}

void Engine::WorldUISystem::Update(CScene* pScene, float deltaTime)
{
}

void Engine::WorldUISystem::Render(CScene* pScene)
{

    App::Print(POSITIONX, POSITIONY, UITEXT.c_str(), COLOR[0], COLOR[1], COLOR[2]);
}

void Engine::WorldUISystem::End(CScene* pScene)
{
}

void Engine::WorldUISystem::Cleanup()
{
}
