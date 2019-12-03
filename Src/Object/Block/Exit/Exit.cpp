/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Exit.cpp
*/

#include "Exit.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "ParticleComponent.hpp"
#include "Map.hpp"
#include "IScene.hpp"

#include <algorithm>

namespace ind
{
    Exit::Exit(
        IScene &scene,
        std::vector<std::string> tags
    ) : Block(scene, tags)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Box/box.3ds");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Box/material_NORMAL.png");
        getComponent<AnimatedMeshComponent>()->setScale(irr::core::vector3df(0.8f, 0.2f, 0.8f));
        getComponent<AnimatedMeshComponent>()->getNode()->setName("exit");

        Factory::createComponent<StaticCollisionComponent>(this);

        Factory::createComponent<ParticleComponent>(this);
        getComponent<ParticleComponent>()->setCallbackFunction([this](void){
            irr::core::vector3df pos = getComponent<AnimatedMeshComponent>()->getPosition();

            return (irr::core::aabbox3df(pos.X - 2, 0, pos.Z - 2, pos.X + 2, 0, pos.Z + 2));
        });
        getComponent<ParticleComponent>()->addBoxEmitter(
            irr::core::aabbox3df(),
            irr::core::vector3df(0.0f, 0.03f, 0.0f),
            20,
            50,
            irr::video::SColor(0, 34, 113, 169),
            irr::video::SColor(0, 126, 189, 232),
            1500,
            2000,
            0,
            irr::core::dimension2df(2.0f, 2.0f),
            irr::core::dimension2df(3.0f, 3.0f)
        );
        getComponent<ParticleComponent>()->addFadeOutAffector(
            irr::video::SColor(255, 0, 0, 0),
            1000);
        getComponent<ParticleComponent>()->getParticleSystem()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    }

    void Exit::update(float delta)
    {
        Object::update(delta);
    }

    Exit::~Exit()
    {
    }
}
