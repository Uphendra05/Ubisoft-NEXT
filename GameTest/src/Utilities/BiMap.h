#pragma once
#ifndef _BIMAP_H
#define _BIMAP_H

#include <iostream>
#include <unordered_map>


namespace Engine
{
    template <typename Key, typename Value>
    class BiMap
    {
    public:
        void Insert(const Key& key, const Value& value)
        {
            if (keyToValue.count(key) > 0 || valueToKey.count(value) > 0)
            {
                throw std::runtime_error("Key or value already exists in the BiMap.");
            }

            keyToValue[key] = value;
            valueToKey[value] = key;
        }

        void RemoveByKey(const Key& key)
        {
            auto it = keyToValue.find(key);
            if (it != keyToValue.end())
            {
                valueToKey.erase(it->second);
                keyToValue.erase(it);
            }
        }
        void RemoveByValue(const Value& value)
        {
            auto it = valueToKey.find(value);
            if (it != valueToKey.end())
            {
                keyToValue.erase(it->second);
                valueToKey.erase(it);
            }
        }

        void Update(const Key& key, const Value& value)
        {
            RemoveByKey(key);
            Insert(key, value);
        }
       

        const Value& GetByKey(const Key& key) const
        {
            auto it = keyToValue.find(key);
            if (it == keyToValue.end())
            {
                throw std::runtime_error("Key not found in the BiMap.");
            }
            return it->second;
        }

        const Key& GetByValue(const Value& value) const
        {
            auto it = valueToKey.find(value);
            if (it == valueToKey.end())
            {
                throw std::runtime_error("Value not found in the BiMap.");
            }
            return it->second;
        }

        bool GetByKey(const Key& key, Value& value) 
        {
            auto it = keyToValue.find(key);

            if (it == keyToValue.end())
            {
                value = Value();
                return false;
            }

            value = it->second;
            return true;
        }

        bool GetByValue(const Value& value, Key& key) 
        {
            auto it = valueToKey.find(value);

            if (it == valueToKey.end())
            {
                key = Key();
                return false;
            }

            key = it->second;
            return true;
        }


        bool ContainsKey(const Key& key) const
        {
            return keyToValue.count(key) > 0;
        }

        bool ContainsValue(const Value& value) const
        {
            return valueToKey.count(value) > 0;
        }



        void Clear()
        {
            keyToValue.clear();
            valueToKey.clear();
        }

    private:
        std::unordered_map<Key, Value> keyToValue;
        std::unordered_map<Value, Key> valueToKey;
    };
    
   

}
#endif