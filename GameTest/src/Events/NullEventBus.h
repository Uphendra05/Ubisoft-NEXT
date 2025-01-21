#pragma once
#ifndef _NULLEVENTBUS_H
#define _NULLEVENTBUS_H

#include "iEventBus.h"
#include "Event.hpp"
#include <functional>
#include <unordered_map>


//*******************************************************************************************
//  NullEventBuss
//*******************************************************************************************
/* Checks for null events
 */
namespace Engine
{
    // Null service only to avoid crashes in locator
    template <typename T>
    class NullEventBus : public iEventBus<T>
    {
    private:
        using EventHandler = iEventBus<T>::EventHandler;

    public:
        NullEventBus() {}
        virtual ~NullEventBus() {};

        // Subscribe to an event
        virtual void Subscribe(T eventType, const EventHandler& handler) {};

        // Publish an event to all the listeners
        virtual void Publish(const Event<T>& event) {};
    };
}
#endif