/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Block
*/

#include "Block.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"

namespace ind {
    Block::Block(IScene &scene, std::vector<std::string> tags) :
        Object(scene, tags)
    {
        Factory::createComponent<AnimatedMeshComponent>(this);
    }
}