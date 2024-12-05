#pragma once

#include <iostream>
#include <vector>

using Entity = uint64_t;

class EntityManager
{
    Entity nextEntity = 0;
    std::vector<Entity> entityList;

public:
    Entity CreateEntity();
   

    void DestroyEntity(Entity entity);

    const std::vector<Entity>& GetEntities() const;

};

