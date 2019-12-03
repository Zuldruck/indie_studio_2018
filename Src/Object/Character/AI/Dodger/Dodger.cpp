/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Dodger
*/

#include "Dodger.hpp"

namespace ind {

Dodger::Dodger(IScene &scene, std::vector<std::string> tags) : AI(scene, tags)
{
    getComponent<AnimatedMeshComponent>()->setMeshFromFile("Mobs/Dodger/dodger.b3d");
    getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Mobs/Dodger/dodger.jpg");
    getComponent<AnimatedMeshComponent>()->addAnimation("dodger_walk", {10, 50, (50 - 10) / 2});
    getComponent<AnimatedMeshComponent>()->addAnimation("dodger_idle", {65, 265, (265 - 65) / 2});
    getComponent<AnimatedMeshComponent>()->addAnimation("dodger_die", {265, 300, (300 - 265) / 2});
    getComponent<AnimatedMeshComponent>()->getNode()->setName("dodger");
    getComponent<MovementComponent>()->setSpeed(DEFAULT_DODGER_SPEED);
    Factory::createComponent<MonsterCollisionComponent>(this);
    Factory::createComponent<MobStaticCollisionComponent>(this);
    setFileName(AI_PATH + std::string("dodger.lua"));
}

}
