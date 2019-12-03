/*
** EPITECH_PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** BomberMan
*/

#ifndef BOMBERMAN_HPP_
#define BOMBERMAN_HPP_

#include "Character.hpp"

#define DEFAULT_BOMBERMAN_SPEED 0.035
#define DEFAULT_RANGE 2
#define DEFAULT_BOMB 1

#define SPEED_BONUS_MULTIPLIER 0.1

namespace ind {
    class Bomb;

    /**
     * @brief BomberMan is the main Character of the Game.
     * It can place Bombs.
     *
     */
    class BomberMan : public Character {
    public:
        /**
         * @brief Construct a new Bomber Man object
         *
         * @param scene The scene we will add this object
         * @param tags Tags that Fence object will have
         */
        BomberMan(
                IScene &scene,
                std::vector<std::string> tags = {"CHARACTER", "PLAYER"});

        /**
         * @brief Update the BomberMan object
         *
         * @param delta Time since the last update
         */
        void    update(float delta) noexcept;

        /**
         * @brief Add or remove a speed bonus to the BomberMan
         *
         * @param modifier +1 or -1
         */
        void    modifyBonusSpeed(int modifier) noexcept;

        /**
         * @brief Add or remove a range bonus to the BomberMan
         *
         * @param modifier +1 or -1
         */
        void    modifyBonusRange(int modifier) noexcept;

        /**
         * @brief Add or remove a bomb to the BomberMan
         *
         * @param modifier +1 or -1
         */
        void    modifyBonusBomb(int modifier) noexcept;

        /**
         * @brief Get the Speed of the BomberMan
         *
         * @return float Speed of the BomberMan
         */
        float   getSpeed(void) noexcept;

        /**
         * @brief Get the Range of the BomberMan
         *
         * @return int Range of the BomberMan
         */
        int     getRange(void) const noexcept;

        /**
         * @brief Get the Bomb of the BomberMan
         *
         * @return int Bomb of the BomberMan
         */
        int     getBomb(void) const noexcept;


        /**
         * @brief Get the number of Speed Bonus
         *
         * @return int number of Speed Bonus
         */
        int     getBonusSpeed(void) const noexcept;

        /**
         * @brief Get the number of Range Bonus
         *
         * @return int number of Range Bonus
         */
        int     getBonusRange(void) const noexcept;

        /**
         * @brief Get the number of Bomb Bonus
         *
         * @return int number of Bomb Bonus
         */
        int     getBonusBomb(void) const noexcept;

        void setBonusSpeed(int bonusSpeed);

        void setBonusRange(int bonusRange);

        void setBonusBomb(int bonusBomb);

    private:
        int _bonusSpeed = 0;
        int _bonusRange = 0;
        int _bonusBomb = 0;
    };
}

#endif /* !BOMBERMAN_HPP_ */
