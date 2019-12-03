/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Fire
*/

#include "Fire.hpp"
#include "IScene.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"
#include "ParticleComponent.hpp"
#include "Map.hpp"

namespace ind {
    Fire::Fire(IScene &scene, std::vector<std::string> tags)
        : Object(scene, tags), _position(0, 0, 0), _aliveTime(FIRE_ALIVE_TIME)
    {
        Factory::createComponent<AnimatedMeshComponent>(this);
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Fire/box.3ds");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Fire/black.png");
        getComponent<AnimatedMeshComponent>()->setScale(irr::core::vector3df(0.85f, 0.85f, 0.85f));
        getComponent<AnimatedMeshComponent>()->getNode()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        getComponent<AnimatedMeshComponent>()->getNode()->setName("fire");
        Factory::createComponent<StaticCollisionComponent>(this);
        Factory::createComponent<ParticleComponent>(this);
        getComponent<ParticleComponent>()->setCallbackFunction([this](void){
            irr::core::vector3df pos = _position * 10;

            return (irr::core::aabbox3df(pos.X - 5, 5, pos.Z - 5, pos.X + 5, 5, pos.Z + 5));
        });
        getComponent<ParticleComponent>()->addBoxEmitter(
            irr::core::aabbox3df(),
            irr::core::vector3df(0.01f, 0.01f, 0.0f),
            150,
            200,
            irr::video::SColor(255, 215, 80, 29),
            irr::video::SColor(255, 235, 95, 35),
            300,
            450,
            360,
            irr::core::dimension2df(1.5f, 1.5f),
            irr::core::dimension2df(3.0f, 3.0f));
        getComponent<ParticleComponent>()->addFadeOutAffector(
            irr::video::SColor(255, 0, 0, 0),
            250);
        getComponent<ParticleComponent>()->getParticleSystem()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        _map = std::static_pointer_cast<Map>(getScene().getObjectsByTags("MAP")[0]);
    }

    void    Fire::update(float delta) noexcept
    {
        Object::update(delta);
        _aliveTime -= delta;
        if (_aliveTime <= 0)
            extinguish();
        else if (_aliveTime <= FIRE_ALIVE_TIME / 3)
            getComponent<ParticleComponent>()->desactivate();
    }

    void    Fire::extinguish(void) noexcept
    {
        _map->getMap()[_position.Z][_position.X] = Map::BlockType::EMPTY;
        _scene.removeObject(this);
    }

    void    Fire::resetAliveTime(void) noexcept
    {
        _aliveTime = FIRE_ALIVE_TIME;
    }

    void    Fire::setPosition(irr::core::vector3df position) noexcept
    {
        _position = position;
        getComponent<AnimatedMeshComponent>()->setPosition(position * 10);
    }

    void    Fire::setAliveTime(float aliveTime) noexcept
    {
        _aliveTime = aliveTime;
    }

    irr::core::vector3df    Fire::getPosition(void) const noexcept
    {
        return _position;
    }
}
