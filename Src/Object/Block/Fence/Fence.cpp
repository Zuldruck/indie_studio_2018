/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Fence
*/

#include "Fence.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"

namespace ind {
    Fence::Fence(IScene &scene, std::vector<std::string> tags) :
        Block(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Fence/fence.3ds");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Fence/material_COLOR.png", 0);
        getComponent<AnimatedMeshComponent>()->setScale(irr::core::vector3df(1.3f, 1.3f, 1.3f));
        getComponent<AnimatedMeshComponent>()->getNode()->setName("fence");
        Factory::createComponent<StaticCollisionComponent>(this);
    }
}