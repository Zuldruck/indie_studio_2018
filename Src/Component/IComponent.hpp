/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "Includes.hpp"

namespace ind {

    class IObject;
    /**
     * @brief IComponent is the interface to implement a Component. A component represent a functionnality and is bind to an object. (see ECS)
     * 
     */
    class IComponent {
        public:
            virtual ~IComponent() = default;

            /**
             * @brief Called when everythings has been created
             * 
             */
            virtual void beginPlay(void) = 0;
            /**
             * @brief Update the component. Called every frames (/rates)
             * 
             * @param delta 
             */
            virtual void update(float delta) = 0;

            /**
             * @brief Pause and unpause the component.
             * 
             */
            virtual void pause(void) = 0;
            /**
             * @brief Tell is the component is activated.
             * 
             * @return true 
             * @return false 
             */
            virtual bool isActivate(void) const noexcept = 0;
            /**
             * @brief Activate the component
             * 
             */
            virtual void activate(void) noexcept = 0;
            /**
             * @brief Desactivate the component
             * 
             */
            virtual void desactivate(void) noexcept = 0;
            /**
             * @brief Get the Owner object
             * 
             * @return IObject* 
             */
            virtual IObject *getOwner(void) const noexcept = 0;
    };
}

#endif /* !ICOMPONENT_HPP_ */