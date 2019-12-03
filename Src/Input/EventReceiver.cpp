/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Input
*/

#include <Src/Scene/GameScene/GameScene.hpp>
#include "MenuScene.hpp"
#include "EventReceiver.hpp"
#include "EventComponent.hpp"
#include "IObject.hpp"
#include "IScene.hpp"

namespace ind {
    EventReceiver::EventReceiver(IScene &scene)
            : _scene(scene)
    {
        for (irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; ++i)
            _keyIsDown[i] = false;
    }

    void EventReceiver::setJoysticks(irr::IrrlichtDevice *device)
    {
        _joystickInfo = _scene.getCore().getJoysticks();
        if (_joystickInfo.size() != 0) {
            if (_joystickInfo.size() < _eventComponents.size()) {
                for (irr::u32 i = 0; i != _joystickInfo.size(); i++) {
                    _eventComponents[_eventComponents.size() - 1 - i]->setJoystick(_joystickInfo[_joystickInfo.size() - 1 - i]);
                }
            } else {
                for (size_t i = 0; i != _eventComponents.size(); i++) {
                    _eventComponents[i]->setJoystick(_joystickInfo[i]);
                }
            }
        }
    }

    bool    EventReceiver::OnEvent(const irr::SEvent& event)
    {
        if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
            _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            if (event.KeyInput.Key == irr::KEY_ESCAPE && event.KeyInput.PressedDown && !static_cast<GameScene *>(&_scene)->isIsGameOver()) {
                _scene.getCore().getEngineSound()->playSong("buttonClicked");
                _scene.pause();
            } else if (event.KeyInput.Key == irr::KEY_F4)
                _scene.getCore().stop();

            BOOST_FOREACH(auto &comp, _eventComponents)
                            comp->updateEvent();
        } else if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
            auto joystickEvt = event.JoystickEvent;
            BOOST_FOREACH(auto &comp, _eventComponents) {
                            if (joystickEvt.Joystick >= _joystickInfo.size()) {
                                exit(2);
                            }
                            if (comp->getJoystick().Name == _joystickInfo[joystickEvt.Joystick].Name) {
                                comp->updateJoystick(joystickEvt);
                                break;
                            }
                        }
        } else if (event.EventType == irr::EET_GUI_EVENT) {

            ind::ind_int id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType) {

                case irr::gui::EGET_SCROLL_BAR_CHANGED:
                    if (id == GUI_ID_VOLUME_SCROLL_BAR) {
                        ind::ind_int pos =  static_cast<irr::gui::IGUIScrollBar *>(event.GUIEvent.Caller)->getPos();
                        if (this->_scene.getCore().getEngineSound() != nullptr)
                            this->_scene.getCore().getEngineSound()->controlVolumeSong("gameMusic", pos);
                        else
                            std::cout << "ERRROR ENGINE SOUND WAS NULL" << std::endl;
                    }
                    break;

                case irr::gui::EGET_BUTTON_CLICKED:
                    switch(id) {
                        case GUI_ID_RUN_PRINCIPAL:
                            dynamic_cast<GameScene *>(&_scene)->getGameUi()->cleanScope();
                            dynamic_cast<GameScene *>(&_scene)->getCore().getDevice()->getGUIEnvironment()->clear();
                            if (dynamic_cast<GameScene *>(&_scene)->getNbPlayer() == 1)
                                this->_scene.getCore().saveGame();
                            this->_scene.getCore().loadScene<MenuScene>(false);
                            return true;
                        case GUI_ID_RUN_PAUSE:
                            this->_scene.pause();
                            return true;
                        case GUI_ID_QUIT_BUTTON:
                            if (dynamic_cast<GameScene *>(&_scene)->getNbPlayer() == 1)
                                this->_scene.getCore().saveGame();
                            this->_scene.getCore().stop();
                            return true;
                        default:
                            return false;
                    }
                default:
                    break;
            }
        }
        BOOST_FOREACH(auto &comp, _eventComponents) {
                        comp->updateEvent();
                    }
        return false;
    }

    bool    EventReceiver::IsKeyDown(irr::EKEY_CODE keyCode) const
    {
        return _keyIsDown[keyCode];
    }

    void    EventReceiver::addComponent(std::shared_ptr<EventComponent> event)
    {
        _eventComponents.push_back(event);
        event->setKeydown(_keyIsDown);

    }

    void    EventReceiver::removeComponent(std::shared_ptr<EventComponent> event)
    {
        for(auto it = _eventComponents.begin(); it != _eventComponents.end(); ++it) {
            if (*it == event) {
                _eventComponents.erase(it);
                break;
            }
        }
    }
}
