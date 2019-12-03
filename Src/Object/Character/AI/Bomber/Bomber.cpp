/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomber
*/

#include "Bomber.hpp"
#include "GameScene.hpp"

namespace ind {

Bomber::Bomber(IScene &scene, std::vector<std::string> tags) : AI(scene, tags), BomberMan(scene, tags)
{
    AI::getComponent<AnimatedMeshComponent>()->setMeshFromFile("Bomberman/bomberman.b3d");
    AI::getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Bomberman/bomberman-black.png");
    AI::getComponent<AnimatedMeshComponent>()->getNode()->setName("bomber");
    AI::getComponent<MovementComponent>()->setSpeed(DEFAULT_BOMBERMAN_SPEED);
    Factory::createComponent<MonsterCollisionComponent>(static_cast<AI *>(this));
    if (static_cast<GameScene *>(&scene)->getNbPlayer() == 1) {
        Factory::createComponent<MobStaticCollisionComponent>(static_cast<AI *>(this));
        setFileName(AI_PATH + std::string("bomberSolo.lua"));
    } else {
        setFileName(AI_PATH + std::string("bomberMulti.lua"));
    }
}

}
