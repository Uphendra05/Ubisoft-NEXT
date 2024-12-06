#pragma once

#include<iostream>
#include <bitset>

namespace Engine
{
	using Entity = uint64_t;
	
	using ComponentType = uint8_t;
	using ComponentId = uint32_t;

	const Entity MAX_ENTITIES = 10000;
	const ComponentType MAX_COMPONENTS = 16;

     using EntityMask = std::bitset<MAX_COMPONENTS>;

}