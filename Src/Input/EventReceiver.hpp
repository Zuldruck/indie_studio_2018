/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include "Includes.hpp"

static const std::vector<std::map<std::string, irr::EKEY_CODE>> INPUTS_KEYS = {{
                        {"right", irr::KEY_KEY_D},
                        {"left", irr::KEY_KEY_Q},
                        {"down", irr::KEY_KEY_S},
                        {"up", irr::KEY_KEY_Z},
                        {"bomb", irr::KEY_SPACE}
                    }, {
                        {"right", irr::KEY_RIGHT},
                        {"left", irr::KEY_LEFT},
                        {"down", irr::KEY_DOWN},
                        {"up", irr::KEY_UP},
                        {"bomb", irr::KEY_RETURN}
                    }, {
                        {"right", irr::KEY_HELP},
                        {"left", irr::KEY_HELP},
                        {"down", irr::KEY_HELP},
                        {"up", irr::KEY_HELP},
                        {"bomb", irr::KEY_HELP}
                    }, {
                        {"right", irr::KEY_HELP},
                        {"left", irr::KEY_HELP},
                        {"down", irr::KEY_HELP},
                        {"up", irr::KEY_HELP},
                        {"bomb", irr::KEY_HELP}
                    }};

namespace ind {
    #define IObject_ptr std::shared_ptr<IObject>

    class EventComponent;
    class IObject;
    class IScene;

    /**
     * @brief EventReceiver is the class which is attached to the device and which catch events
     */
    class EventReceiver : public irr::IEventReceiver {
        public:
            /**
             * @brief EventReceiver()
             */
            EventReceiver(IScene &scene);

            /**
             *  @brief ~EventReceiver()
             */
            virtual ~EventReceiver() = default;

            /**
             * @brief This method is called each time there is an event
             *
             * @param event An Event class with information about the event
             * @return false
             */
            virtual bool    OnEvent(const irr::SEvent & event);

            /**
             * @brief This is used to check whether a key is being
             *
             * @param keyCode
             * @return true or false according the state of the key
             */
            virtual bool    IsKeyDown(irr::EKEY_CODE keyCode) const;

            /**
             * @brief Add an EventComponent to the EventComponent's vector
             * 
             * @param event EventComponent to add
             */
            void            addComponent(std::shared_ptr<EventComponent> event);

            /**
             * @brief Initialize all present joysticks
             * 
             * @param device 
             */
            void setJoysticks(irr::IrrlichtDevice *device);

            /**
             * @brief Remove an EventComponent from the EventComponent's vector
             * 
             * @param event EventComponent to remove
             */
            void            removeComponent(std::shared_ptr<EventComponent> event);

        private:
            IScene &_scene;
            irr::core::array<irr::SJoystickInfo> _joystickInfo;
            std::vector<std::shared_ptr<EventComponent>>    _eventComponents;
            bool                            _keyIsDown[irr::KEY_KEY_CODES_COUNT];

    };
}

#endif /* !INPUT_HPP_ */
