#include "stdafx.h"
#include "PlayerUtilities.h"
#include "src/ECS/SComponents.h"



namespace Engine
{
	Entity Engine::PlayerUtilities::GetPlayerID(CScene* pScene)
	{
		SComponentIterator<MovementComponent>::Iterator it = SComponentIterator<MovementComponent>(*pScene).begin();

		return *it;
	}

	Entity PlayerUtilities::GetMirroPlayerID(CScene* pScene)
	{
		SComponentIterator<MovementComponent>::Iterator it = SComponentIterator<MovementComponent>(*pScene).begin();

		++it;

		return *it;
	}
}

