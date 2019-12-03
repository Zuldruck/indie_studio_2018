/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** EventComponent.cpp
*/

#include "EventComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"
#include "MovementComponent.hpp"
#include "AnimatedMeshComponent.hpp"
#include "BombComponent.hpp"
#include "BomberMan.hpp"
#include "GameScene.hpp"
#include "ParticleComponent.hpp"
#include "Factory.hpp"

#define MOVEMENT_COMPONENT _owner->getComponent<MovementComponent>()

namespace ind {
    EventComponent::EventComponent(IObject *owner, bool isActivated)
    : Component(owner, isActivated), _velocityUpdated(false), _velocity(0, 0, 0)
    {
        _joystick.Name = "none";
    }

    EventComponent::~EventComponent()
    {
    }

    void    EventComponent::beginPlay(void)
    {
        MOVEMENT_COMPONENT->updateMovement();
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            _keyIsPressed[i] = false;
    }

    void EventComponent::setJoystick(irr::SJoystickInfo info)
    {
        _joystick = info;

        switch(_joystick.PovHat) {
            case irr::SJoystickInfo::POV_HAT_PRESENT:
                break;
            case irr::SJoystickInfo::POV_HAT_ABSENT:
                break;
            case irr::SJoystickInfo::POV_HAT_UNKNOWN:
            default:
                break;
        }
    }

    const irr::SJoystickInfo &EventComponent::getJoystick() const
    {
        return _joystick;
    }

    void EventComponent::pause(void)
    {
        Component::pause();
    }

    bool    EventComponent::isKeyPressed(irr::EKEY_CODE key)
    {
        if (_keyIsDown[key] == true && _keyIsPressed[key] == false) {
            _keyIsPressed[key] = true;
            _velocityUpdated = true;
            return (true);
        }
        return (false);
    }

    bool    EventComponent::isKeyReleased(irr::EKEY_CODE key)
    {
        if (_keyIsDown[key] == false && _keyIsPressed[key] == true) {
            _keyIsPressed[key] = false;
            _velocityUpdated = true;
            return (true);
        }
        return (false);
    }

    void    EventComponent::updateEvent(void)
    {
        if (!isActivate() || _paused || _joystick.Name != "none")
            return;
        if (!_inputs.empty()) {
            _velocityUpdated = false;

            if (isKeyPressed(_inputs["right"]) == true) {
                _velocity.X += 1;
            } else if (isKeyReleased(_inputs["right"]) == true) {
                _velocity.X -= 1;
            }

            if (isKeyPressed(_inputs["left"]) == true) {
                _velocity.X += -1;
            } else if (isKeyReleased(_inputs["left"]) == true) {
                _velocity.X -= -1;
            }

            if (isKeyPressed(_inputs["down"]) == true) {
                _velocity.Z += -1;
            } else if (isKeyReleased(_inputs["down"]) == true) {
                _velocity.Z -= -1;
            }

            if (isKeyPressed(_inputs["up"]) == true) {
                _velocity.Z += 1;
            } else if (isKeyReleased(_inputs["up"]) == true) {
                _velocity.Z -= 1;
            }

            if (isKeyPressed(_inputs["bomb"]) == true)
                static_cast<BomberMan *>(_owner)->getComponent<BombComponent>()->arm();
            isKeyReleased(_inputs["bomb"]);

            if (_velocityUpdated == true) {
                MOVEMENT_COMPONENT->setDirection(_velocity);
                MOVEMENT_COMPONENT->updateMovement();
            }
        }
    }
    
    void EventComponent::updateJoystick(irr::SEvent::SJoystickEvent &joystickEvent)
    {
        if (_paused || !isActivate() || _joystick.Name == "none")
            return;
        auto x = joystickEvent.Axis[joystickEvent.AXIS_X];
        auto y = joystickEvent.Axis[joystickEvent.AXIS_Y];
        _velocity.X = x / 32767;
        _velocity.Z = -y / 32767;
        MOVEMENT_COMPONENT->setDirection(_velocity);
        MOVEMENT_COMPONENT->updateMovement();
        if (joystickEvent.ButtonStates == 4 || joystickEvent.ButtonStates == 8 || 
        joystickEvent.ButtonStates == 1 || joystickEvent.ButtonStates == 2)
            static_cast<BomberMan *>(_owner)->getComponent<BombComponent>()->arm();
    }

    void    EventComponent::setKeydown(bool *keyIsDown)
    {
        _keyIsDown = keyIsDown;
    }

    void    EventComponent::setInputs(std::map<std::string, irr::EKEY_CODE> inputs)
    {
        _inputs = inputs;
    }
}
