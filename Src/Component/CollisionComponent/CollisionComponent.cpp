/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CollisionComponent
*/

#include "CollisionComponent.hpp"
#include "Factory.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "AI.hpp"

namespace ind {
    StaticCollisionComponent::StaticCollisionComponent(IObject *owner, bool isActivated)
    : Component(owner, isActivated)
    {
        _meshComponent = _owner->getComponent<AnimatedMeshComponent>();
        _owner->getScene().getCollisionManager()->addStaticCollision(_meshComponent->getNode());
    }

    StaticCollisionComponent::~StaticCollisionComponent()
    {
        auto e = _meshComponent->getNode()->getTriangleSelector();

        _owner->getScene().getCollisionManager()->removeCollision(e);
    }

    std::shared_ptr<AnimatedMeshComponent> &StaticCollisionComponent::getMeshComponent(void) noexcept
    {
        return _meshComponent;
    }

    void    StaticCollisionComponent::activate(void) noexcept
    {
        if (_isActivated)
            return;
        auto e = _meshComponent->getNode()->getTriangleSelector();

        _owner->getScene().getCollisionManager()->addCollision(e);
        _isActivated = true;
    }

    void    StaticCollisionComponent::desactivate(void) noexcept
    {
        if (!_isActivated)
            return;
        auto e = _meshComponent->getNode()->getTriangleSelector();

        _owner->getScene().getCollisionManager()->removeCollision(e);
        _isActivated = false;
    }
    

    MobStaticCollisionComponent::MobStaticCollisionComponent(IObject *owner, bool isActivated)
    : Component(owner, isActivated)
    {
        _mesh = _owner->getScene().getManager()->addAnimatedMeshSceneNode(
            _owner->getScene().getManager()->getMesh((MODELS_OFFSET + std::string("Fire/box.3ds")).c_str()),
            0,
            -1,
            irr::core::vector3df(0, 0, 0),
            irr::core::vector3df(0, 0, 0),
            irr::core::vector3df(0.8f, 0.1f, 0.8f),
            true
        );
        _mesh->setMaterialTexture(0, _owner->getScene().getCore().getDriver()->getTexture((TEXTURES_OFFSET + std::string("Fire/black.png")).c_str()));
        _mesh->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        _mesh->setName("mobCollision");
        _owner->getScene().getCollisionManager()->addStaticCollision(_mesh);
    }

    MobStaticCollisionComponent::~MobStaticCollisionComponent()
    {
        auto selector = _mesh->getTriangleSelector();

        _owner->getScene().getCollisionManager()->removeCollision(selector);
        _mesh->remove();
    }

    void    MobStaticCollisionComponent::update(float delta) noexcept
    {
        auto pos = _owner->getComponent<AnimatedMeshComponent>()->getPosition();

        _mesh->setPosition(irr::core::vector3df(pos.X, 0, pos.Z));
    }
}