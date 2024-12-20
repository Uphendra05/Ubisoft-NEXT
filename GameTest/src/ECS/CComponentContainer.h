#pragma once
#ifndef _CCOMPONENTCONTAINER_H
#define _CCOMPONENTCONTAINER_H

#include "ECSCore.h"

namespace Engine
{
	class CComponentContainer
	{
	public :

		CComponentContainer(unsigned int size);
		~CComponentContainer();

		void* Get(ComponentId compId);
		void* Add( ComponentId& compIdReplace);
		void  Remove(ComponentId& compId);

		unsigned int Size() const;

	private:

		char* mData;        
		unsigned int mSize;        
		unsigned int mElementSize;


	};
}
#endif
