/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#include "Bomb.hpp"
#include "IScene.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "CollisionComponent.hpp"
#include "BombComponent.hpp"
#include "ParticleComponent.hpp"
#include "BomberMan.hpp"
#include "Map.hpp"
#include "Fire.hpp"
#include "Box.hpp"
#include "Bomber.hpp"

namespace ind {
    Bomb::Bomb(IScene &scene, std::vector<std::string> tags)
        : Object(scene, tags), _isArm(false), _aliveTime(BOMB_ALIVE_TIME)
    {
        Factory::createComponent<AnimatedMeshComponent>(this);
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Bomb/bomb.obj");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Bomb/bomb.png");
        getComponent<AnimatedMeshComponent>()->getNode()->setName("bomb");
        getComponent<AnimatedMeshComponent>()->desactivate();
        Factory::createComponent<StaticCollisionComponent>(this);
        getComponent<StaticCollisionComponent>()->desactivate();
        Factory::createComponent<ParticleComponent>(this);
        getComponent<ParticleComponent>()->setCallbackFunction([this](void){
            return getComponent<AnimatedMeshComponent>()->getPosition();
        });
        getComponent<ParticleComponent>()->addBoxEmitter(
            getComponent<AnimatedMeshComponent>()->getPosition(),
            irr::core::vector3df(0.005f, 0.012f, 0.0f),
            50,
            75,
            irr::video::SColor(0, 215, 80, 29),
            irr::video::SColor(0, 235, 95, 35),
            400,
            650,
            15,
            irr::core::dimension2df(0.1f,0.1f),
            irr::core::dimension2df(0.3f,0.3f));
        getComponent<ParticleComponent>()->addFadeOutAffector(
            irr::video::SColor(255, 0, 0, 0),
            250);
        getComponent<ParticleComponent>()->getParticleSystem()->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
        getComponent<ParticleComponent>()->setPositionOffset(irr::core::vector3df(0.4f, 6.0f, 0.0f));
        getComponent<ParticleComponent>()->desactivate();
    }

    Bomb::~Bomb()
    {
    }

    void                        Bomb::beginPlay(void) noexcept
    {
        Object::beginPlay();
        _engineSound = getScene().getCore().getEngineSound();
    }

    void                        Bomb::update(float delta) noexcept
    {
        Object::update(delta);
        if (_isArm) {
            if (getComponent<StaticCollisionComponent>()->isActivate() == false &&
            checkIfPlayerIsOnTheBomb() == false) {
                getComponent<StaticCollisionComponent>()->activate();
            }
            _aliveTime -= delta;
            if (_aliveTime <= 0)
                explode(true);
        }
    }

    irr::core::vector3df        Bomb::adaptPositionToMap(irr::core::vector3df position) noexcept
    {
        irr::core::vector3df newPosition;

        newPosition.X = static_cast<int>((position.X / 10) + 0.5);
        newPosition.Z = static_cast<int>((position.Z / 10) + 0.5);
        return (newPosition);
    }

    bool                        Bomb::checkIfBombCanBePlaced(void) noexcept
    {
        auto map = std::static_pointer_cast<Map>(_scene.getObjectsByTags("MAP")[0]);

        if (_position.X < 0 || _position.X >= map->getWidth()
        || _position.Z < 0 || _position.Z >= map->getHeight())
            return (false);
        if (map->getMap()[_position.Z][_position.X] == Map::BlockType::EMPTY) {
            map->getMap()[_position.Z][_position.X] = Map::BlockType::BOMB;
            return (true);
        }
        return (false);
    }

    bool                        Bomb::checkIfPlayerIsOnTheBomb(void) noexcept
    {
        irr::core::aabbox3df playerBox = _bomberManOwner->getComponent<AnimatedMeshComponent>()->getNode()->getBoundingBox();
        irr::core::vector3df playerPos = _bomberManOwner->getComponent<AnimatedMeshComponent>()->getPosition();
        irr::core::vector3df radius = playerBox.MaxEdge - playerBox.getCenter();
        irr::core::vector3df summits[4] = {
            {playerPos.X + radius.X, 0, playerPos.Z + radius.Z},
            {playerPos.X - radius.X, 0, playerPos.Z + radius.Z},
            {playerPos.X + radius.X, 0, playerPos.Z - radius.Z},
            {playerPos.X - radius.X, 0, playerPos.Z - radius.Z}
        };

        for (int i = 0; i < 4; i++) {
            irr::core::vector3df adaptedSummit = adaptPositionToMap(summits[i]);
            if (adaptedSummit.X == _position.X && adaptedSummit.Z == _position.Z)
                return (true);
        }
        return (false);
    }

    void                        Bomb::browseFires(irr::core::vector3df newFirePosition) noexcept
    {
        BOOST_FOREACH(auto & object, getScene().getObjectsByTags("FIRE")) {
            if (std::static_pointer_cast<Fire>(object)->getPosition() == newFirePosition) {
                std::static_pointer_cast<Fire>(object)->resetAliveTime();
                break;
            }
        }
    }

    void                        Bomb::browseBombs(irr::core::vector3df newFirePosition) noexcept
    {
        BOOST_FOREACH(auto & object, getScene().getObjectsByTags("BOMB")) {
            if (std::static_pointer_cast<Bomb>(object)->getPosition() == newFirePosition) {
                std::static_pointer_cast<Bomb>(object)->explode(true);
                break;
            }
        }
    }

    void                        Bomb::browseBoxes(irr::core::vector3df newFirePosition) noexcept
    {
        BOOST_FOREACH(auto & object, getScene().getObjectsByTags("BOX")) {
            if (object->getComponent<AnimatedMeshComponent>()->getPosition() / 10 == newFirePosition) {
                std::static_pointer_cast<Box>(object)->destroy();
                break;
            }
        }
    }

    void                        Bomb::createFire(Map::BlockType * actualBlock, irr::core::vector3df newFirePosition) noexcept
    {
        std::shared_ptr<Fire> newFire;

        *actualBlock = Map::BlockType::FIRE;
        newFire = Factory::createObject<Fire>(getScene());
        newFire->setPosition(irr::core::vector3df(newFirePosition.X, 0, newFirePosition.Z));
    }

    bool                        Bomb::handleFireCases(Map::BlockType * actualBlock, irr::core::vector3df newFirePosition) noexcept
    {
        if (*actualBlock == Map::BlockType::EMPTY) {
            createFire(actualBlock, newFirePosition);
            return (true);
        } else if (*actualBlock == Map::BlockType::FIRE) {
            browseFires(newFirePosition);
            return (true);
        } else if (*actualBlock == Map::BlockType::BOMB) {
            browseBombs(newFirePosition);
            return (false);
        } else if (*actualBlock == Map::BlockType::BOX) {
            browseBoxes(newFirePosition);
            createFire(actualBlock, newFirePosition);
            return (false);
        }
        return (false);
    }

    void                        Bomb::propagateFire(void) noexcept
    {
        auto map = std::static_pointer_cast<Map>(_scene.getObjectsByTags("MAP")[0]);
        std::vector<std::vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        Map::BlockType * actualBlock = &map->getMap()[_position.Z][_position.X];
        irr::core::vector3df newFirePosition = _position;

        _engineSound->playSong("fireWave");
        createFire(actualBlock, newFirePosition);
        for (unsigned int dir = 0; dir < directions.size(); dir++) {
            for (int i = 1; i <= _bomberManOwner->getRange(); i++) {
                newFirePosition.X = _position.X + (directions[dir][1] * i);
                newFirePosition.Z = _position.Z + (directions[dir][0] * i);
                actualBlock = &map->getMap()[newFirePosition.Z][newFirePosition.X];
                if (handleFireCases(actualBlock, newFirePosition) == false)
                    break;
            }
        }
    }

    void                        Bomb::setBomberManOwner(BomberMan * bomberManOwner) noexcept
    {
        _bomberManOwner = bomberManOwner;
    }

    void                        Bomb::arm(void) noexcept
    {
        irr::core::vector3df pos;

        _engineSound->playSong("bombDeposited");
        if (dynamic_cast<Bomber *>(_bomberManOwner))
            pos = static_cast<AI *>(dynamic_cast<Bomber *>(_bomberManOwner))->getComponent<AnimatedMeshComponent>()->getPosition();
        else
            pos = _bomberManOwner->getComponent<AnimatedMeshComponent>()->getPosition();
        _position = adaptPositionToMap(pos);
        if (checkIfBombCanBePlaced() == false)
            return;
        getComponent<AnimatedMeshComponent>()->setPosition(_position * 10);
        getComponent<AnimatedMeshComponent>()->activate();
        getComponent<ParticleComponent>()->activate();
        _isArm = true;
    }

    void                        Bomb::explode(bool silentMode) noexcept
    {
        auto map = std::static_pointer_cast<Map>(_scene.getObjectsByTags("MAP")[0]);

        map->getMap()[_position.Z][_position.X] = Map::BlockType::EMPTY;
        if (silentMode) {
            _engineSound->playSong("bombExplosion");
            propagateFire();
        }
        getComponent<AnimatedMeshComponent>()->desactivate();
        getComponent<StaticCollisionComponent>()->desactivate();
        getComponent<ParticleComponent>()->desactivate();
        getComponent<ParticleComponent>()->getParticleSystem()->clearParticles();
        _isArm = false;
        _aliveTime = BOMB_ALIVE_TIME;
    }

    void                        Bomb::setAliveTime(float aliveTime) noexcept
    {
        _aliveTime = aliveTime;
    }

    BomberMan *Bomb::getBomberManOwner(void) noexcept
    {
        return _bomberManOwner;
    }

    bool                        Bomb::isArm(void) const noexcept
    {
        return _isArm;
    }

    irr::core::vector3df        Bomb::getPosition(void) const noexcept
    {
        return _position;
    }
}
