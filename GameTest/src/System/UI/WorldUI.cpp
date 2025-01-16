#include "stdafx.h"
#include "WorldUI.h"

const float POSITIONX = 200.0f;
const float POSITIONY = 500.0f;
std::string UITEXT = " PRESS WASD TO MOVE ENTITY";
const float COLOR[3] = { 1.0f, 1.0f, 1.0f };


std::string Engine::WorldUI::SystemName()
{
    return std::string();
}

void Engine::WorldUI::Init()
{
}

void Engine::WorldUI::Start(CScene* pScene)
{
}

void Engine::WorldUI::Update(CScene* pScene, float deltaTime)
{
}

void Engine::WorldUI::Render(CScene* pScene)
{

    App::Print(POSITIONX, POSITIONY, UITEXT.c_str(), COLOR[0], COLOR[1], COLOR[2]);
}

void Engine::WorldUI::End(CScene* pScene)
{
}

void Engine::WorldUI::Cleanup()
{
}
