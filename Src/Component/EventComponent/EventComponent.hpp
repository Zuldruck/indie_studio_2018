/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** EventComponent.hpp
*/

#ifndef EVENT_COMPONENT_HPP
#define EVENT_COMPONENT_HPP

#include "Component.hpp"

namespace ind {
    class MovementComponent;

    /**
     * @brief EventComponent is the component who manage keyboard's input in the IObject which own a EventComponent
     */
    class EventComponent : public Component
    {
        public:
            /**
             * @brief Construct the eventComponent
             *
             * @param owner owner is the IObject who own this component
             * @param isActivated bool to activate or not this component
             */
            EventComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destruct l'eventComponent
             *
             */
            ~EventComponent();

            /**
             * @brief Prepare all what we need for painless use this component
             *
             */
            void    beginPlay(void);

            /**
             * @brief Pause the event component
             * 
             */
            virtual void pause(void);

            /**
             * @brief Execute the code of each object which need it
             *
             * @param void
             */
            void    updateEvent(void);

            /**
             * @brief Handle joystick inputs
             * 
             * @param joystickEvent 
             */
            void updateJoystick(irr::SEvent::SJoystickEvent &joystickEvent);

            /**
             * @brief Return true or false according to the state of the key passed in parameters
             *
             * @param key
             */
            bool    isKeyPressed(irr::EKEY_CODE key);

            /**
             * @brief Return true or false according to the state of the key passed in parameters
             *
             * @param key irr::EKEY_CODE which is pressed or not
             * @return return true if the key is pressed else false
             */
            bool    isKeyReleased(irr::EKEY_CODE key);

            /**
             * @brief Set the pointer to the array of keyDown
             *
             * @param key irr::EKEY_CODE which is pressed or not
             * @return return true if the key is pressed else false
             */
            void    setKeydown(bool *KeyIsDown);

            /**
             * @brief Set the Joystick 
             * 
             * @param info 
             */
            void setJoystick(irr::SJoystickInfo info);

            /**
             * @brief Get the Joystick
             * 
             * @return const irr::SJoystickInfo& 
             */
            const irr::SJoystickInfo &getJoystick() const;

            /**
             * @brief Set the map of EKEY_CODE used to detects Inputs
             * 
             * @param inputs map of EKEY_CODE
             */
            void    setInputs(std::map<std::string, irr::EKEY_CODE> inputs);

        protected:
            bool *                                  _keyIsDown;
            bool                                    _keyIsPressed[irr::KEY_KEY_CODES_COUNT];
            std::shared_ptr<MovementComponent>      _movComp;

            irr::SJoystickInfo                      _joystick;
            bool                                    _velocityUpdated;
            irr::core::vector3df                    _velocity;
            std::map<std::string, irr::EKEY_CODE>   _inputs;
    };
}

#endif /* !EVENT_COMPONENT_HPP */