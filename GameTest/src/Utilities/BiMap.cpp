#include "BiMap.h"

namespace Engine
{
    template <typename Key, typename Value>
    void BiMap<Key, Value>::Insert(const Key& key, const Value& value)
    {
        if (keyToValue.count(key) > 0 || valueToKey.count(value) > 0) 
        {
            throw std::runtime_error("Key or value already exists in the BiMap.");
        }

        keyToValue[key] = value;
        valueToKey[value] = key;
    }

    // Remove by key
    template <typename Key, typename Value>
    void BiMap<Key, Value>::RemoveByKey(const Key& key)
    {
        auto it = keyToValue.find(key);
        if (it != keyToValue.end()) 
        {
            valueToKey.erase(it->second);
            keyToValue.erase(it);
        }
    }

    // Remove by value
    template <typename Key, typename Value>
    void BiMap<Key, Value>::RemoveByValue(const Value& value)
    {
        auto it = valueToKey.find(value);
        if (it != valueToKey.end()) 
        {
            keyToValue.erase(it->second);
            valueToKey.erase(it);
        }
    }

    template <typename Key, typename Value>
    void BiMap<Key, Value>::Update(const Key& key, const Value& value)
    {
        RemoveByKey(key);
        Insert(key, value);
    }


    // Get value by key
    template <typename Key, typename Value>
    const Value& BiMap<Key, Value>::GetByKey(const Key& key) const
    {
        auto it = keyToValue.find(key);
        if (it == keyToValue.end()) 
        {
            throw std::runtime_error("Key not found in the BiMap.");
        }
        return it->second;
    }

    // Get key by value
    template <typename Key, typename Value>
    const Key& BiMap<Key, Value>::GetByValue(const Value& value) const
    {
        auto it = valueToKey.find(value);
        if (it == valueToKey.end()) 
        {
            throw std::runtime_error("Value not found in the BiMap.");
        }
        return it->second;
    }

    // Check if key exists
    template <typename Key, typename Value>
    bool BiMap<Key, Value>::ContainsKey(const Key& key) const
    {
        return keyToValue.count(key) > 0;
    }

    // Check if value exists
    template <typename Key, typename Value>
    bool BiMap<Key, Value>::ContainsValue(const Value& value) const
    {
        return valueToKey.count(value) > 0;
    }

    // Clear the map
    template <typename Key, typename Value>
    void BiMap<Key, Value>::Clear()
    {
        keyToValue.clear();
        valueToKey.clear();
    }
}