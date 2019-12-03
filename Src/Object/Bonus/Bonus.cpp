/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Bonus.hpp
*/

#include "Bonus.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"
#include "ParticleComponent.hpp"

namespace ind
{
    Bonus::Bonus(IScene &scene, std::vector<std::string> tags) : Object(scene, tags)
    {
        auto random = static_cast<double>(Utils::generateRandomNumber(0, 100)) / 100;
        auto particleColor = irr::video::SColor();
        
        _type = static_cast<BonusType>(random < CHANCE_TO_GET_MALUS ? -1 : 1);
        _effect = static_cast<BonusEffect>(Utils::generateRandomNumber(0, 2));
        particleColor = _type == -1 ? irr::video::SColor(255, 163, 0, 105) : irr::video::SColor(255, 255, 234, 167);
        std::string pathMesh = "Bonus/";
        if (_effect == SPEED)
            pathMesh += "speed-";
        else if (_effect == RANGE)
            pathMesh += "fire-";
        else if (_effect == BOMB)
            pathMesh += "bomb-";
        if (_type == BONUS) {
            pathMesh += "bonus.b3d";
        } else {
            pathMesh += "malus.b3d";
        }
        Factory::createComponent<AnimatedMeshComponent>(this);
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Bonus/fire-bonus.b3d");
        getComponent<AnimatedMeshComponent>()->getNode()->setName("bonus");
        getComponent<AnimatedMeshComponent>()->addAnimation("bonus_rotate", {0, 120, 60});
        getComponent<AnimatedMeshComponent>()->playAnimation("bonus_rotate", true);
        Factory::createComponent<StaticCollisionComponent>(this);
        Factory::createComponent<ParticleComponent>(this);
        getComponent<ParticleComponent>()->setCallbackFunction([this](void){
            return getComponent<AnimatedMeshComponent>()->getPosition();
        });
        getComponent<ParticleComponent>()->addRingEmitter(
            getComponent<AnimatedMeshComponent>()->getPosition(),
            3.0f,
            1.0f,
            irr::core::vector3df(0.0f, 0.03f, 0.0f),
            10,
            15,
            particleColor,
            particleColor + irr::video::SColor(0, 25, 30, 25),
            750,
            1000,
            0,
            irr::core::dimension2df(1.0f,1.0f),
            irr::core::dimension2df(1.5f,1.5f));
        getComponent<ParticleComponent>()->addFadeOutAffector(
            irr::video::SColor(255, 0, 0, 0),
            500);
        getComponent<ParticleComponent>()->getParticleSystem()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
    }

    Bonus::~Bonus()
    {
    }

    BonusType Bonus::getType(void) const noexcept
    {
        return _type;
    }

    BonusEffect Bonus::getEffect(void) const noexcept
    {
        return _effect;
    }

    void Bonus::setToBoxPosition(Box *box)
    {
        irr::core::vector3df boxPos = box->getComponent<AnimatedMeshComponent>()->getNode()->getPosition();
        getComponent<AnimatedMeshComponent>()->getNode()->setPosition(boxPos);
    }

    void Bonus::beginPlay(void)
    {
    }

    void Bonus::update(float delta)
    {
        Object::update(delta);
        getComponent<AnimatedMeshComponent>()->getNode()->setRotation(irr::core::vector3df(0, 0, 1));
    }
}