/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "BomberMan.hpp"

#define TIME_AFTER_WIN 1500

namespace ind {
    /**
     * @brief Player is a BomberMan which catch Inputs and is manipulated by a real player
     * 
     */
    class Player : public BomberMan {
    public:

        /**
         * @brief Construct a new Player object
         *
         * @param scene The scene we will add this object
         * @param tags Tags that Fence object will have
         */
        Player(IScene &scene, std::vector<std::string> tags = {"PLAYER", "CHARACTER", "BOMBERMAN"});

        /**
         * @brief Destroy the Player object
         *
         */
        ~Player();

        /**
         * @brief Update the Player object
         * 
         * @param delta Time since the last update
         */
        void    update(float delta) noexcept;

        /**
         * @brief The player has won
         * 
         */
        void    win(void) noexcept;

        /**
         * @brief get If the player has won
         * 
         * @return true the player has won
         * @return false the player hasn't win
         */
        bool    hasWon(void) const noexcept;

        private:
            bool    _hasWon;
            int     _timeAfterWin;
    };
}

#endif /* !PLAYER_HPP_ */
