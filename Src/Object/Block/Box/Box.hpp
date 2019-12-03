/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "Block.hpp"

#define BONUS_SPAWNRATE 0.12

namespace ind {

    /**
     * @brief Box is a breakable Block which is destroy by Fire.
     * It is randomly placed on the Map
     * 
     */
    class Box : public Block {
        public:

            /**
             * @brief Construct a new Box object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Box object will have
             */
            Box(
                IScene &scene,
                std::vector<std::string> tags = {"BOX"});

            /**
             * @brief Destroy the Box object
             * 
             */
            ~Box() = default;

            /**
             * @brief Trigger when is destroy by Fire. Randomly spawn a Bonus or a Malus
             * 
             */
            void    destroy(void) noexcept;
    };
}

#endif /* !BOX_HPP_ */
