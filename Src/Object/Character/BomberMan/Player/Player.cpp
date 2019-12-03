/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#include "Player.hpp"
#include "IScene.hpp"
#include "AnimatedMeshComponent.hpp"
#include "BombComponent.hpp"
#include "MovementComponent.hpp"
#include "ParticleComponent.hpp"
#include "Factory.hpp"
#include "EventComponent.hpp"
#include "PlayerCollisionComponent.hpp"
#include "Map.hpp"
#include "GameScene.hpp"

namespace ind {

    Player::Player(IScene &scene, std::vector<std::string> tags)
    : BomberMan(scene, tags), _hasWon(false), _timeAfterWin(0)
    {
        getComponent<AnimatedMeshComponent>()->setMeshFromFile("Bomberman/bomberman.b3d");
        getComponent<AnimatedMeshComponent>()->setMaterialTextureFromFile("Bomberman/bomberman.png");
        getComponent<AnimatedMeshComponent>()->getNode()->setName("player");
        getComponent<MovementComponent>()->setSpeed(DEFAULT_BOMBERMAN_SPEED);
        Factory::createComponent<EventComponent>(this);
        Factory::createComponent<PlayerCollisionComponent>(this);
    }

    Player::~Player()
    {
    }

    void    Player::update(float delta) noexcept
    {
        BomberMan::update(delta);
        if (_hasWon == true) {
            _timeAfterWin += delta;
            if (_timeAfterWin >= TIME_AFTER_WIN) {
                dynamic_cast<GameScene *>(&getScene())->getEngineSound()->playSong("teleportation");
                std::static_pointer_cast<Map>(getScene().getObjectsByTags("MAP")[0])->nextLevel();
                getComponent<AnimatedMeshComponent>()->playAnimation("bomberman_idle", true);
                getComponent<MovementComponent>()->setDirection(irr::core::vector3df());
                getComponent<MovementComponent>()->activate();
                getComponent<EventComponent>()->activate();
                getComponent<BombComponent>()->activate();
                _hasWon = false;
                _timeAfterWin = 0;
            }
        }
    }

    void    Player::win(void) noexcept
    {
        _hasWon = true;
    }

    bool    Player::hasWon(void) const noexcept
    {
        return _hasWon;
    }
}
