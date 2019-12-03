/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Block
*/

#ifndef BLOCK_HPP_
#define BLOCK_HPP_

#include "Object.hpp"

namespace ind {

    /**
     * @brief Block is a static Object with an AnimatedMeshComponent
     * 
     */
    class Block : public Object {
        public:

            /**
             * @brief Construct a new Block object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Block(
                IScene &scene,
                std::vector<std::string> tags = {"BLOCK"});

            /**
             * @brief Destroy the Block object
             * 
             */
            virtual ~Block() = default;
    };
}

#endif /* !BLOCK_HPP_ */
