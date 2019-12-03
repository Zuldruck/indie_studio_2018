/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Component
*/

#include "Component.hpp"

namespace ind {
    Component::Component(IObject *owner, bool isActivated)
    : _owner(owner),
    _isActivated(isActivated)
    {
    }

    Component::~Component()
    {
        
    }

    void Component::beginPlay(void)
    {
    }

    void Component::update(float delta)
    {
    }
    
    void Component::pause(void)
    {
        if (_paused) {
            _paused = false;
        } else {
            _paused = true;
        }
    }

    bool Component::isActivate(void) const noexcept
    {
        return _isActivated;
    }

    void Component::activate(void) noexcept
    {
        _isActivated = true;
    }

    void Component::desactivate(void) noexcept
    {
        _isActivated = false;
    }

    IObject *Component::getOwner(void) const noexcept
    {
        return _owner;
    }
}