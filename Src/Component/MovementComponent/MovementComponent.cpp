/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** MovementComponent
*/

#include "MovementComponent.hpp"
#include "IScene.hpp"
#include "IObject.hpp"
#include "AnimatedMeshComponent.hpp"
#include "ParticleComponent.hpp"
#include "Character.hpp"
#include "AI.hpp"

#define ANIMATED_MESH_COMPONENT _owner->getComponent<AnimatedMeshComponent>()
#define PARTICLE_COMPONENT _owner->getComponent<ParticleComponent>()

namespace ind {
    MovementComponent::MovementComponent(IObject * owner, bool isActivated)
    : Component(owner, isActivated), _speed(0), _direction(0, 0, 0), _idleOffsetMovement(IDLE_OFFSET_MOVEMENT)
    {
    }

    MovementComponent::~MovementComponent()
    {
    }

    void    MovementComponent::beginPlay(void) noexcept
    {
        _animatedMesh = _owner->getComponent<AnimatedMeshComponent>();
    }

    void    MovementComponent::update(float delta) noexcept
    {
        if (!isActivate())
            return;
        
        auto pos = _animatedMesh->getPosition();
        if (isMoving()) {
            _animatedMesh->setPosition(irr::core::vector3df(pos.X, 0, pos.Z) + (_direction * _speed * delta));
        } else {
            _animatedMesh->setPosition(irr::core::vector3df(pos.X, _idleOffsetMovement, pos.Z));
            _idleOffsetMovement *= -1;
        }
        _animatedMesh->getNode()->updateAbsolutePosition();
    }

    void    MovementComponent::updateMovement(void) noexcept
    {
        int degree = -1;

        if (_direction.X == 0 && _direction.Z == 1) {
            degree = 180;
        } else if (_direction.X == 0 && _direction.Z == -1) {
            degree = 0;
        } else if (_direction.X == 1 && _direction.Z == 0) {
            degree = -90;
        } else if (_direction.X == -1 && _direction.Z == 0) {
            degree = 90;
        } else if (_direction.X == 1 && _direction.Z == 1) {
            degree = -135;
        } else if (_direction.X == 1 && _direction.Z == -1) {
            degree = -45;
        } else if (_direction.X == -1 && _direction.Z == 1) {
            degree = 135;
        } else if (_direction.X == -1 && _direction.Z == -1) {
            degree = 45;
        }
        if (degree != -1)
            ANIMATED_MESH_COMPONENT->getNode()->setRotation(irr::core::vector3df(0, degree, 0));

        if (isMoving()) {
            if (_owner->hasTag("BOMBERMAN"))
                ANIMATED_MESH_COMPONENT->playAnimation("bomberman_walk", true);
            else if (_owner->hasTag("BLOB"))
                ANIMATED_MESH_COMPONENT->playAnimation("blob_walk", true);
            else if (_owner->hasTag("LEEROY"))
                ANIMATED_MESH_COMPONENT->playAnimation("leeroy_walk", true);
            else if (_owner->hasTag("DODGER"))
                ANIMATED_MESH_COMPONENT->playAnimation("dodger_walk", true);
            PARTICLE_COMPONENT->activate();
        } else {
            if (_owner->hasTag("BOMBERMAN"))
                ANIMATED_MESH_COMPONENT->playAnimation("bomberman_idle", true);
            else if (_owner->hasTag("BLOB"))
                ANIMATED_MESH_COMPONENT->playAnimation("blob_idle", true);
            else if (_owner->hasTag("DODGER"))
                ANIMATED_MESH_COMPONENT->playAnimation("dodger_idle", true);
            PARTICLE_COMPONENT->desactivate();
        }
    }

    bool    MovementComponent::isMoving(void) noexcept
    {
        if (_direction.X != 0 || _direction.Z != 0)
            return (true);
        return (false);
    }

    void    MovementComponent::setSpeed(const float speed) noexcept
    {
        _speed = speed;
    }

    void    MovementComponent::setDirection(const irr::core::vector3df & direction) noexcept
    {
        _direction = direction;
    }

    void    MovementComponent::setDirectionX(const float directionX) noexcept
    {
        _direction.X = directionX;
    }

    void    MovementComponent::setDirectionY(const float directionY) noexcept
    {
        _direction.Y = directionY;
    }

    void    MovementComponent::setDirectionZ(const float directionZ) noexcept
    {
        _direction.Z = directionZ;
    }

    irr::core::vector3df    MovementComponent::getDirection(void) const noexcept
    {
        return _direction;
    }

    float                   MovementComponent::getSpeed(void) const noexcept
    {
        return _speed;
    }
}
