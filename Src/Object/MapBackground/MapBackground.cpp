/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** MapBackground
*/

#include "MapBackground.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"

namespace ind {
    MapBackground::MapBackground(IScene &scene, std::vector<std::string> tags) :
            Object(scene, tags)
    {
        Factory::createComponent<AnimatedMeshComponent>(this);
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("map2.3ds");
    }
}
