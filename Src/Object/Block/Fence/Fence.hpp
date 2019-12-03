/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Fence
*/

#ifndef FENCE_HPP_
#define FENCE_HPP_

#include "Block.hpp"

namespace ind {

    /**
     * @brief Fence is an unbreakable Block which surround the Map
     * 
     */
    class Fence : public Block {
        public:

            /**
             * @brief Construct a new Fence object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Fence(
                IScene &scene,
                std::vector<std::string> tags = {"FENCE"});

            /**
             * @brief Destroy the Fence object
             * 
             */
            virtual ~Fence() = default;
    };
}

#endif /* !FENCE_HPP_ */
