/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Factory
*/

#include "Factory.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "EventComponent.hpp"
#include "MovementComponent.hpp"
#include "CollisionComponent.hpp"
#include "PlayerCollisionComponent.hpp"
#include "MonsterCollisionComponent.hpp"
#include "BombComponent.hpp"
#include "ParticleComponent.hpp"
#include "Fence.hpp"
#include "Wall.hpp"
#include "Box.hpp"
#include "Map.hpp"
#include "BomberMan.hpp"
#include "Bomb.hpp"
#include "Fire.hpp"
#include "MapBackground.hpp"
#include "Exit.hpp"
#include "Blob.hpp"
#include "Bomber.hpp"
#include "Player.hpp"
#include "Dodger.hpp"
#include "Leeroy.hpp"
#include "GameCamera.hpp"
#include "GameLight.hpp"
#include "Bonus.hpp"

namespace ind
{
    template <>
    std::shared_ptr<Bonus>                    Factory::createObject(IScene &scene)
    {
        std::shared_ptr<Bonus> newBonus = std::make_shared<Bonus>(scene);

        scene.addObject(newBonus);
        return (newBonus);
    }

    template <>
    std::shared_ptr<Fence>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Fence> newFence = std::make_shared<Fence>(scene);

        scene.addObject(newFence);
        return (newFence);
    }

    template <>
    std::shared_ptr<Wall>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Wall> newWall = std::make_shared<Wall>(scene);

        scene.addObject(newWall);
        return (newWall);
    }

    template <>
    std::shared_ptr<Box>                    Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Box> newBox = std::make_shared<Box>(scene);

        scene.addObject(newBox);
        return (newBox);
    }

    template <>
    std::shared_ptr<Map>                    Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Map> newMap = std::make_shared<Map>(scene);

        scene.addObject(newMap);
        return (newMap);
    }

    template<>
    std::shared_ptr<Exit>          Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Exit> newExit = std::make_shared<Exit>(scene);

        scene.addObject(newExit);
        return (newExit);
    }

    template <>
    std::shared_ptr<MapBackground>                    Factory::createObject(IScene & scene)
    {
        std::shared_ptr<MapBackground> newMapBackground = std::make_shared<MapBackground>(scene);

        scene.addObject(newMapBackground);
        return (newMapBackground);
    }

    template <>
    std::shared_ptr<Bomb>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Bomb> newBomb = std::make_shared<Bomb>(scene);

        scene.addObject(newBomb);
        return (newBomb);
    }

    template <>
    std::shared_ptr<Fire>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Fire> newFire = std::make_shared<Fire>(scene);

        scene.addObject(newFire);
        return (newFire);
    }

    template <>
    std::shared_ptr<GameLight>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<GameLight> newGameLight = std::make_shared<GameLight>(scene);

        scene.addObject(newGameLight);
        return (newGameLight);
    }

    template <>
    std::shared_ptr<GameCamera>                   Factory::createObject(IScene & scene)
    {
        std::shared_ptr<GameCamera> newGameCamera = std::make_shared<GameCamera>(scene);

        scene.addObject(newGameCamera);
        return (newGameCamera);
    }


    template <>
    std::shared_ptr<Bomber>              Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Bomber> newBomber = std::make_shared<Bomber>(scene);

        scene.addObject(std::static_pointer_cast<AI>(newBomber));
        return (newBomber);
    }

    template <>
    std::shared_ptr<Blob>              Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Blob> newBlob = std::make_shared<Blob>(scene);

        scene.addObject(newBlob);
        return (newBlob);
    }

    template <>
    std::shared_ptr<Player>              Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Player> newBlob = std::make_shared<Player>(scene);

        scene.addObject(newBlob);
        return (newBlob);
    }

    template <>
    std::shared_ptr<Leeroy>              Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Leeroy> newLeeroy = std::make_shared<Leeroy>(scene);

        scene.addObject(newLeeroy);
        return (newLeeroy);
    }

    template <>
    std::shared_ptr<Dodger>              Factory::createObject(IScene & scene)
    {
        std::shared_ptr<Dodger> newDodger = std::make_shared<Dodger>(scene);

        scene.addObject(newDodger);
        return (newDodger);
    }

    template <>
    std::shared_ptr<AnimatedMeshComponent>  Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<AnimatedMeshComponent> newAnimatedMeshComponent = std::make_shared<AnimatedMeshComponent>(owner, isActivated);

        owner->addComponent(newAnimatedMeshComponent);
        return (newAnimatedMeshComponent);
    }

    template <>
    std::shared_ptr<MovementComponent>      Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<MovementComponent> newMovementComponent = std::make_shared<MovementComponent>(owner, isActivated);

        owner->addComponent(newMovementComponent);
        return (newMovementComponent);
    }

    template <>
    std::shared_ptr<EventComponent>         Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<EventComponent> newEventComponent = std::make_shared<EventComponent>(owner, isActivated);

        owner->addComponent(newEventComponent);
        owner->getScene().getEventReceiver()->addComponent(newEventComponent);
        return (newEventComponent);
    }

    template <>
    std::shared_ptr<StaticCollisionComponent>     Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<StaticCollisionComponent> newStaticCollisionComponent = std::make_shared<StaticCollisionComponent>(owner, isActivated);

        owner->addComponent(newStaticCollisionComponent);
        return (newStaticCollisionComponent);
    }

    template <>
    std::shared_ptr<PlayerCollisionComponent>     Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<PlayerCollisionComponent> newPlayerCollisionComponent = std::make_shared<PlayerCollisionComponent>(owner, isActivated);

        owner->addComponent(newPlayerCollisionComponent);
        return (newPlayerCollisionComponent);
    }

    template <>
    std::shared_ptr<MonsterCollisionComponent>     Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<MonsterCollisionComponent> newMonsterCollisionComponent = std::make_shared<MonsterCollisionComponent>(owner, isActivated);

        owner->addComponent(newMonsterCollisionComponent);
        return (newMonsterCollisionComponent);
    }

    template <>
    std::shared_ptr<MobStaticCollisionComponent>              Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<MobStaticCollisionComponent> newMobStaticCollisionComponent = std::make_shared<MobStaticCollisionComponent>(owner, isActivated);

        owner->addComponent(newMobStaticCollisionComponent);
        return (newMobStaticCollisionComponent);
    }

    template <>
    std::shared_ptr<BombComponent>     Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<BombComponent> newBombComponent = std::make_shared<BombComponent>(owner, isActivated);

        owner->addComponent(newBombComponent);
        return (newBombComponent);
    }
    
    template <>
    std::shared_ptr<ParticleComponent>     Factory::createComponent(
        IObject *owner,
        bool isActivated)
    {
        std::shared_ptr<ParticleComponent> newParticleComponent = std::make_shared<ParticleComponent>(owner, isActivated);

        owner->addComponent(newParticleComponent);
        return (newParticleComponent);
    }
}
