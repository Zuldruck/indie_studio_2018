/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CollisionManager
*/

#include "CollisionManager.hpp"
#include "AnimatedMeshComponent.hpp"
#include "IObject.hpp"
#include "Core.hpp"

namespace ind {
    CollisionManager::CollisionManager(irr::scene::ISceneManager * scene)
    : _scene(scene)
    {
        _metaSelector = _scene->createMetaTriangleSelector();
    }

    CollisionManager::~CollisionManager()
    {
        _metaSelector->drop();
    }

    void    CollisionManager::beginPlay(void) noexcept
    {
    }

    void CollisionManager::addStaticCollision(irr::scene::IAnimatedMeshSceneNode * mesh) noexcept
    {
        irr::scene::ITriangleSelector * selector = _scene->createTriangleSelectorFromBoundingBox(mesh);

        mesh->setTriangleSelector(selector);
        _metaSelector->addTriangleSelector(selector);
        selector->drop();
    }

    void CollisionManager::addPlayerCollision(irr::scene::IAnimatedMeshSceneNode * mesh, PlayerCollisionComponent *comp) noexcept
    {
        irr::scene::ITriangleSelector * selector = _scene->createTriangleSelectorFromBoundingBox(mesh);
        const irr::core::aabbox3d<irr::f32>& box = mesh->getBoundingBox();
        irr::core::vector3df radius = box.MaxEdge - box.getCenter();
        irr::scene::ISceneNodeAnimatorCollisionResponse* anim = _scene->createCollisionResponseAnimator(_metaSelector, mesh, radius * 0.8, irr::core::vector3df());

        anim->setCollisionCallback(comp);
        mesh->addAnimator(anim);
        mesh->setTriangleSelector(selector);
        selector->drop();
        anim->drop();
    }

    void CollisionManager::addMonsterCollision(irr::scene::IAnimatedMeshSceneNode * mesh, MonsterCollisionComponent *comp) noexcept
    {
        irr::scene::ITriangleSelector * selector = _scene->createTriangleSelectorFromBoundingBox(mesh);
        const irr::core::aabbox3d<irr::f32>& box = mesh->getBoundingBox();
        irr::core::vector3df radius = box.MaxEdge - box.getCenter();
        irr::scene::ISceneNodeAnimatorCollisionResponse* anim = _scene->createCollisionResponseAnimator(_metaSelector, mesh, radius / 2, irr::core::vector3df(), irr::core::vector3df(0, -(radius.Y), 0));

        anim->setCollisionCallback(comp);
        mesh->addAnimator(anim);
        mesh->setTriangleSelector(selector);
        selector->drop();
        anim->drop();
    }

    void CollisionManager::removeCollision(irr::scene::ITriangleSelector *triangle) noexcept
    {
        _metaSelector->removeTriangleSelector(triangle);
    }

    void CollisionManager::addCollision(irr::scene::ITriangleSelector *triangle) noexcept
    {
        _metaSelector->addTriangleSelector(triangle);
    }

}