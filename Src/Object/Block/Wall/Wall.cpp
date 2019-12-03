/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Wall
*/

#include "Wall.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"

namespace ind {
    Wall::Wall(IScene &scene, std::vector<std::string> tags) :
        Block(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Wall/wall.3ds");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Wall/material_COLOR.png", 0);
        getComponent<AnimatedMeshComponent>()->setScale(irr::core::vector3df(0.90f, 0.9f, 0.90f));
        getComponent<AnimatedMeshComponent>()->getNode()->setName("wall");
        Factory::createComponent<StaticCollisionComponent>(this);
    }
}
