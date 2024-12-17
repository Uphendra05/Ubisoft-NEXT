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
        void Insert(const Key& key, const Value& value);
        void RemoveByKey(const Key& key);
        void RemoveByValue(const Value& value);
        void Update(const Key& key, const Value& value);
       

        const Value& GetByKey(const Key& key) const;
        const Key& GetByValue(const Value& value) const;

        bool ContainsKey(const Key& key) const;
        bool ContainsValue(const Value& value) const;



        void Clear();

    private:
        std::unordered_map<Key, Value> keyToValue;
        std::unordered_map<Value, Key> valueToKey;
    };
    
   

}
#endif