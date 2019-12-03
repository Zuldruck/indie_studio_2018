/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Leeroy
*/

#include "Leeroy.hpp"

namespace ind {
    Leeroy::Leeroy(IScene &scene, std::vector<std::string> tags) : AI(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Mobs/Leeroy/leeroy.b3d");
        getComponent<AnimatedMeshComponent>()->addAnimation("leeroy_walk", {10, 30, (30 - 10) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("leeroy_die", {100, 116, (116 - 100) / 2});
        getComponent<AnimatedMeshComponent>()->getNode()->setName("leeroy");
        getComponent<MovementComponent>()->setSpeed(DEFAULT_LEEROY_SPEED);
        Factory::createComponent<MonsterCollisionComponent>(this);
        Factory::createComponent<MobStaticCollisionComponent>(this);
        setFileName(AI_PATH + std::string("leeroy.lua"));
    }
}
