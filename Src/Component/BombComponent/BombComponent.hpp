/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** BombComponent
*/

#ifndef BOMBCOMPONENT_HPP_
#define BOMBCOMPONENT_HPP_

#include "Component.hpp"

#define Bomb_ptr std::shared_ptr<Bomb>

namespace ind {
    class IObject;
    class Bomb;

    /**
     * @brief BombComponent is a Class which allows the creation and the manipulation of a bomb
     * 
     */
    class BombComponent : public Component {
        public:
            /**
             * @brief Construct a new BombComponent
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            BombComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the BombComponent
             * 
             */
            ~BombComponent();

            /**
             * @brief Add a Bomb in the Bombs vector
             * 
             */
            void            addBomb(void) noexcept;

            /**
             * @brief Remove a Bomb from the Bombs vector
             * 
             */
            void            removeBomb(void) noexcept;

            /**
             * @brief Arm the first Bomb which is not disarmed
             * 
             */
            void            arm(void) noexcept;

            /**
             * @brief Get the number of Bombs in the Bombs vector
             * 
             * @return unsigned int Number of Bombs in the Bombs vector
             */
            unsigned int    getNumberBomb(void) const noexcept;

            /**
             * @brief Get the Available Bombs object
             * 
             * @return int 
             */
            unsigned        getAvailableBombs(void) const noexcept;

        protected:
            std::vector<Bomb_ptr>   _bombs;
    };
}

#endif /* !BOMBCOMPONENT_HPP_ */
