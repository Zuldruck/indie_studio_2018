/*
** EPITECH PROJECT,
** OOP_indie_studio_2018
** File description:
** BomberMan
*/

#include "BomberMan.hpp"
#include "IScene.hpp"
#include "Factory.hpp"
#include "AnimatedMeshComponent.hpp"
#include "EventComponent.hpp"
#include "MovementComponent.hpp"
#include "BombComponent.hpp"
#include "ParticleComponent.hpp"
#include "PlayerCollisionComponent.hpp"
#include "Character.hpp"

namespace ind {
    BomberMan::BomberMan(IScene &scene, std::vector<std::string> tags) :
            Character(scene, tags), _bonusSpeed(0), _bonusRange(0), _bonusBomb(0)
    {
        getComponent<AnimatedMeshComponent>()->addAnimation("bomberman_walk", {1, 174, (174 - 1) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("bomberman_idle", {180, 245, (245 - 180) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("bomberman_win", {245, 310, (310 - 245) / 2});
        getComponent<AnimatedMeshComponent>()->addAnimation("bomberman_die", {315, 375, (375 - 315) / 2});
        getComponent<AnimatedMeshComponent>()->getNode()->setName("bomberMan");
        Factory::createComponent<BombComponent>(this);
        for (int i = 0; i < DEFAULT_BOMB; i++)
            getComponent<BombComponent>()->addBomb();
    }

    void    BomberMan::update(float delta) noexcept
    {
        Character::update(delta);
    }

    void    BomberMan::modifyBonusSpeed(int modifier) noexcept
    {
        if (getBonusSpeed() + modifier >= 0) {
            _bonusSpeed += modifier;
            getComponent<MovementComponent>()->setSpeed(getSpeed());
        }
    }

    void    BomberMan::modifyBonusRange(int modifier) noexcept
    {
        if (getBonusRange() + modifier >= 0)
            _bonusRange += modifier;
    }

    void    BomberMan::modifyBonusBomb(int modifier) noexcept
    {
        if (getBonusBomb() + modifier >= 0) {
            _bonusBomb += modifier;
            if (modifier > 0)
                getComponent<BombComponent>()->addBomb();
            else
                getComponent<BombComponent>()->removeBomb();
        }
    }

    float   BomberMan::getSpeed(void) noexcept
    {
        return (DEFAULT_BOMBERMAN_SPEED * (1 + (_bonusSpeed * SPEED_BONUS_MULTIPLIER)));
    }

    int     BomberMan::getRange(void) const noexcept
    {
        return DEFAULT_RANGE + _bonusRange;
    }

    int     BomberMan::getBomb(void) const noexcept
    {
        return DEFAULT_BOMB + _bonusBomb;
    }

    int     BomberMan::getBonusSpeed(void) const noexcept
    {
        return _bonusSpeed;
    }

    int     BomberMan::getBonusRange(void) const noexcept
    {
        return _bonusRange;
    }

    int     BomberMan::getBonusBomb(void) const noexcept
    {
        return _bonusBomb;
    }

    void BomberMan::setBonusSpeed(int bonusSpeed)
    {
        if (bonusSpeed == DEFAULT_BOMBERMAN_SPEED || bonusSpeed <= 0) {
            _bonusSpeed = 0;
            return;
        }
        _bonusSpeed = bonusSpeed;
        getComponent<MovementComponent>()->setSpeed(getSpeed());
    }

    void BomberMan::setBonusRange(int bonusRange)
    {
        if (bonusRange == DEFAULT_RANGE || bonusRange <= 0) {
            _bonusRange = 0;
            return;
        }
        _bonusRange = bonusRange - DEFAULT_RANGE;
    }

    void BomberMan::setBonusBomb(int bonusBomb)
    {
        if (bonusBomb == DEFAULT_BOMB || bonusBomb <= 0) {
            _bonusBomb = 0;
            return;
        }
        for (int i = 0 ; i < bonusBomb - DEFAULT_BOMB; i++) {
            getComponent<BombComponent>()->addBomb();
        }
        _bonusBomb = bonusBomb - DEFAULT_BOMB;
    }

}
