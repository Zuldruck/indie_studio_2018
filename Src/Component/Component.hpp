/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Component
*/

#ifndef COMPONENT_HPP_
#define COMPONENT_HPP_

#include "IComponent.hpp"

namespace ind {
    /**
     * @brief Simple implementation of IComponent
     * 
     */
    class Component : public IComponent {
        public:
        /**
         * @brief Construct a new Component object
         * 
         * @param owner 
         * @param isActivated 
         */
            Component(IObject *owner, bool isActivated = true);
            virtual ~Component();

            /**
             * @brief Simple implementation of IComponent (doing nothing)
             * 
             */
            virtual void    beginPlay(void);
            /**
             * @brief Simple implementation of IComponent (doing nothing)
             * 
             */
            virtual void    update(float delta);

            /**
             * @brief Pause and unpause the component.
             * 
             */
            virtual void pause(void);
            /**
             * @brief Simple implementation of IComponent
             * 
             */
            virtual bool    isActivate(void) const noexcept;
            /**
             * @brief Simple implementation of IComponent
             * 
             */
            virtual void    activate(void) noexcept;
            /**
             * @brief Simple implementation of IComponent
             * 
             */
            virtual void    desactivate(void) noexcept;

            /**
             * @brief Get the Owner object
             * 
             * @return IObject* 
             */
            virtual IObject *       getOwner(void) const noexcept;

        protected:
            bool _paused = false;
            IObject *   _owner;
            bool        _isActivated;
    };
}

#endif /* !COMPONENT_HPP_ */
