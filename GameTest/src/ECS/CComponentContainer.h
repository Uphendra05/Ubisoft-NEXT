#pragma once
#ifndef _CCOMPONENTCONTAINER_H
#define _CCOMPONENTCONTAINER_H

#include "ECSCore.h"


//*******************************************************************************************
// ComponentContainer
//*******************************************************************************************
/* This class manages a dynamic array of components in the Engine more like a Component Storage. 
   It allows adding, retrieving, and removing components using unique IDs. 
 */

namespace Engine
{
	class CComponentContainer
	{
	public :

		CComponentContainer(unsigned int size);
		~CComponentContainer();

		void* GetComponent(ComponentId compId); //Get The component using the ID
		void* Add( ComponentId& compIdReplace); //Add The component to the Container using the ID
		void  Remove(ComponentId& compId); //Remove from the Container using the ID

		unsigned int Size() const;

	private:

		char* mData;        
		unsigned int mSize;
		unsigned int mElementSize;


	};
}
#endif
