/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Wall
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "Block.hpp"

namespace ind {

    /**
     * @brief Wall is an unbreakable Block which is placed following a Map pattern
     * 
     */
    class Wall : public Block {
        public:

            /**
             * @brief Construct a new Wall object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Wall(
                IScene &scene,
                std::vector<std::string> tags = {"WALL"});

            /**
             * @brief Destroy the Wall object
             * 
             */
            virtual ~Wall() = default;
    };
}

#endif /* !WALL_HPP_ */
