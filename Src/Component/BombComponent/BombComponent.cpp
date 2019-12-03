/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** BombComponent
*/

#include "BombComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "Bomb.hpp"
#include "Factory.hpp"
#include "BomberMan.hpp"

namespace ind {
    BombComponent::BombComponent(IObject *owner, bool isActivated)
        : Component(owner, isActivated)
    {
    }

    BombComponent::~BombComponent()
    {
    }

    void            BombComponent::addBomb(void) noexcept
    {
        auto newBomb = Factory::createObject<Bomb>(_owner->getScene());

        newBomb->setBomberManOwner(static_cast<BomberMan *>(_owner));
        _bombs.push_back(newBomb);
    }

    void            BombComponent::removeBomb(void) noexcept
    {
        _bombs.pop_back();
    }

    void            BombComponent::arm(void) noexcept
    {
        if (!isActivate())
            return;
        BOOST_FOREACH(auto & bomb, _bombs) {
            if (bomb->isArm() == false) {
                bomb->arm();
                break;
            }
        }
    }

    unsigned int    BombComponent::getNumberBomb(void) const noexcept
    {
        return _bombs.size();
    }

    unsigned        BombComponent::getAvailableBombs(void) const noexcept
    {
        unsigned count = 0;

        BOOST_FOREACH(auto &bomb, _bombs) {
            if (bomb->isArm() == false)
                count += 1;
        }
        return 1;
    }
}
