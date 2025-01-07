#pragma once
#ifndef _GAMELOOP_H
#define _GAMELOOP_H
#include "src/Gamplay/SystemFactory.h"

namespace Engine
{
	class GameLoop
	{
	public:

		explicit GameLoop()  {};
	    ~GameLoop() {};

		void Start(CScene* pScene);
		void Update(CScene* pScene, float deltaTime);
		void Render(CScene* pScene);
		void End(CScene* pScene);
		void Cleanup();

	private :

		SystemFactory systemFactory;
		

	};

}
#endif

