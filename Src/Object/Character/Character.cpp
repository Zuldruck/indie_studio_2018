/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Character
*/

#include <Src/Scene/GameScene/GameScene.hpp>
#include "Character.hpp"
#include "Factory.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "MovementComponent.hpp"
#include "BombComponent.hpp"
#include "EventComponent.hpp"
#include "CollisionComponent.hpp"
#include "BombComponent.hpp"
#include "ParticleComponent.hpp"
#include "Map.hpp"
#include "Bomber.hpp"

namespace ind {
    Character::Character(IScene &scene, std::vector<std::string> tags)
            : Object(scene, tags), _isAlive(true), _timeAfterDie(0)
    {
        Factory::createComponent<AnimatedMeshComponent>(this);
        Factory::createComponent<MovementComponent>(this);
        Factory::createComponent<ParticleComponent>(this);
        getComponent<ParticleComponent>()->setCallbackFunction([this](void){
            return getComponent<AnimatedMeshComponent>()->getPosition();
        });
        getComponent<ParticleComponent>()->addBoxEmitter(
            getComponent<AnimatedMeshComponent>()->getPosition(),
            irr::core::vector3df(0.01f, 0.01f, 0.015f),
            5,
            10,
            irr::video::SColor(0, 155, 118, 83),
            irr::video::SColor(0, 175, 128, 95),
            1000,
            1250,
            45,
            irr::core::dimension2df(0.5f,0.5f),
            irr::core::dimension2df(1.0f,1.0f));
        getComponent<ParticleComponent>()->addGravityAffector(
            irr::core::vector3df(0.0f, -0.002f, 0.003f),
            750);

        _username = "UNDEFINED";
        getComponent<AnimatedMeshComponent>()->getNode()->setName("Character");
    }

    const std::string &Character::getUsername() const
    {
        return _username;
    }

    void Character::setUsername(const std::string &username)
    {
        _username = username;
    }

    Character::~Character()
    {
    }

    void    Character::update(float delta)
    {
        Object::update(delta);
        if (_isAlive == false) {
            _timeAfterDie += delta;
            if (_timeAfterDie >= TIME_AFTER_DIE) {
                if (hasTag("PLAYER") || hasTag("BOMBER"))
                    std::static_pointer_cast<Map>(getScene().getObjectsByTags("MAP")[0])->removePlayer(this);
                getScene().removeObject(this);
            }
        }
    }

    void    Character::die(void) noexcept
    {
        _isAlive = false;
        getComponent<MovementComponent>()->desactivate();
        getComponent<ParticleComponent>()->desactivate();
        if (hasTag("BOMBERMAN")) {
            getComponent<AnimatedMeshComponent>()->playAnimation("bomberman_die", false);
            if (dynamic_cast<Bomber *>(this)) {
                static_cast<BomberMan *>(dynamic_cast<Bomber *>(this))->getComponent<BombComponent>()->desactivate();
            } else {
                getComponent<BombComponent>()->desactivate();
            }
        } else if (hasTag("BLOB")) {
            getComponent<AnimatedMeshComponent>()->playAnimation("blob_die", false);
        } else if (hasTag("LEEROY")) {
            getComponent<AnimatedMeshComponent>()->playAnimation("leeroy_die", false);
        } else if (hasTag("DODGER")) {
            getComponent<AnimatedMeshComponent>()->playAnimation("dodger_die", false);
        }
        if (hasTag("PLAYER") && !dynamic_cast<Bomber *>(this))
            getComponent<EventComponent>()->desactivate();
    }

    bool    Character::isAlive(void) noexcept
    {
        return _isAlive;
    }
}
