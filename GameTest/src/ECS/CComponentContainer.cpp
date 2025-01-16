#include "stdafx.h"
#include "CComponentContainer.h"


namespace Engine
{
    Engine::CComponentContainer::CComponentContainer(unsigned int size) : mElementSize(size)
    {
        // Allocate memory for the component pool
        mSize = 0;
        mData = new char[mElementSize * MAX_ENTITIES];
    }

    Engine::CComponentContainer::~CComponentContainer()
    {
        delete[] mData;
    }

    void* Engine::CComponentContainer::GetComponent(ComponentId compId)
    {
        if (compId >= mSize || mData == nullptr)
        {
            throw std::out_of_range("Invalid ComponentId.");
            return nullptr;
        }

        void* address = mData + compId * mElementSize;
        return address;
    }

    void* Engine::CComponentContainer::Add( ComponentId& compIdReplace)
    {

        if (compIdReplace < mSize)
        {
            // mData + compIdReplace * mElementSize
            void* componentLocation = mData + compIdReplace * mElementSize;                                       // 0x1000 + 3 * 16 = 0x1048 address of the 3rd component
            std::memset(componentLocation, 0, mElementSize);                                                      // std::memset(0x1048, 0, 16) Clears 16 bytes of memory starting at 0x1048.
            return componentLocation;                                                                             // Return the address 0x1048.
        }

        char* newData = new char[(mSize + 1) * mElementSize];


        if (mData != nullptr)
        {
            if (mSize > 0 && mElementSize > std::numeric_limits<size_t>::max() / mSize)
            {
                throw std::overflow_error("Arithmetic overflow in memcpy size calculation");
            }

            std::memcpy(newData, mData, static_cast<size_t>(mSize) * static_cast<size_t>(mElementSize));
            delete[] mData;
        }
        mData = newData;

        void* newComponentLocation = mData + mSize * mElementSize;
        std::memset(newComponentLocation, 0, mElementSize);
       

        // More 1 active component
        ++mSize;

        compIdReplace = mSize - 1;
       

        return newComponentLocation;

        
    }

    void Engine::CComponentContainer::Remove(ComponentId& compId)
    {
        if (compId >= mSize || mData == nullptr)
        {
            throw std::out_of_range("Invalid ComponentId.");
        }

        if (compId == mSize - 1)
        {
            --mSize;
            return;
        }

        // Move the last component to the position of the removed component
        void* source = mData + (mSize - 1) * mElementSize;
        void* destination = mData  + compId * mElementSize;
        std::memcpy(destination, source, mElementSize);

        --mSize;

        // Clear the ID of the removed component
        compId = mSize;
            

    }

    unsigned int Engine::CComponentContainer::Size() const
    {
        return mSize;
    }
}

