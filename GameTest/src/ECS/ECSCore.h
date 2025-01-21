#pragma once
#ifndef _ECSCORE_H
#define _ECSCORE_H


#include<iostream>
#include <bitset>

//*******************************************************************************************
// ECSCore
//*******************************************************************************************
/* Header for all the necessary information for the Entities.

 */

namespace Engine
{
	using Entity = uint64_t;
	
	using ComponentType = uint8_t;
	using ComponentId = uint32_t;

	const Entity MAX_ENTITIES = 10000;
	const ComponentType MAX_COMPONENTS = 16;

    using EntityMask = std::bitset<MAX_COMPONENTS>;

	constexpr uint64_t INDEX_MASK = 0xFFFFFFFF00000000; // High 32 bits
	constexpr uint64_t VERSION_MASK = 0x00000000FFFFFFFF; // Low 32 bits

}
#endif
