/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** Exit.hpp
*/

#ifndef __EXIT_HPP__
#define __EXIT_HPP__

#include "Includes.hpp"
#include "Block.hpp"

namespace ind {


    /**
     * @brief Exit is a block, when we touch it, we are teleported to the next level.
     * It appears at the end of the current level.
     *
     */
    class Exit : public Block
    {
        public:
        /**
         * @brief Construct the teleportation object
         *
         * @param scene The scene we will add this object
         * @param tags Tags that Exit object will have
         */
        Exit(
                IScene &scene,
                std::vector<std::string> tags = {"BLOCK", "EXIT"});

        /**
         * @brief Destruct the teleportation object
         */
        virtual ~Exit();


        /**
         * @brief Update the object
         *
         * @param delta Delta
         */
        virtual void update(float delta);
    };

}

#endif /* !__EXIT_HPP__ */
