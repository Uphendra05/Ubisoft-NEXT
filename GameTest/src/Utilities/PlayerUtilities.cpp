#include "stdafx.h"
#include "PlayerUtilities.h"
#include "src/ECS/SComponents.h"



namespace Engine
{
	Entity Engine::PlayerUtilities::GetPlayerID(CScene* pScene)
	{
		SComponentIterator<ScoreComponent>::Iterator it = SComponentIterator<ScoreComponent>(*pScene).begin();

		return *it;
	}

    Entity PlayerUtilities::GetFogOfWarID(CScene* pScene)
    {
        SComponentIterator<FogOfWarComponent>::Iterator it = SComponentIterator<FogOfWarComponent>(*pScene).begin();

        return *it;
    }

	size_t PlayerUtilities::CalculateResult(size_t strokes, size_t points, size_t multiplier)
	{
        size_t result = points / strokes;
        result *= multiplier;
        return result;
	}

	size_t PlayerUtilities::PointStreaks(size_t strokes, size_t multiplier, eGameStreaks mGameStreaks)
	{
        size_t _points = 0;


        switch (mGameStreaks)
        {
        case HOLEINONE:
            _points = 500;
            return CalculateResult(strokes, _points, multiplier);

            break;
        case TWOTOFOUR:
            _points = 300;
            return CalculateResult(strokes, _points, multiplier);

            break;
        case FIVETOSEVEN:
            _points = 100;

            return CalculateResult(strokes, _points, multiplier);

            break;
        default:
            return size_t();
            break;

        }

	}

	
}

