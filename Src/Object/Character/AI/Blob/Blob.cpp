/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Blob
*/

#include "Blob.hpp"

namespace ind {
    Blob::Blob(IScene &scene, std::vector<std::string> tags) : AI(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Mobs/Blob/blob.b3d");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Mobs/Blob/blob.png");
        getComponent<AnimatedMeshComponent>()->addAnimation("blob_walk", {120, 160, (120 - 160) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("blob_idle", {5, 120, (120 - 5) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("blob_die", {250, 320, (320 - 250) / 2});
        getComponent<AnimatedMeshComponent>()->getNode()->setName("blob");
        getComponent<MovementComponent>()->setSpeed(DEFAULT_BLOB_SPEED);
        Factory::createComponent<MonsterCollisionComponent>(this);
        Factory::createComponent<MobStaticCollisionComponent>(this);
        setFileName(AI_PATH + std::string("random.lua"));
    }
}
