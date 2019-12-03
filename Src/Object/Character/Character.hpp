/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "Object.hpp"

#define TIME_AFTER_DIE 1500

namespace ind {

    /**
     * @brief Character is equipped of an AnimatedMeshComponent and a MovementComponent.
     * It is the base Class of all Players / AI of the Game.
     * 
     */
    class Character : public Object {
        public:
            /**
             * @brief Construct a new Character object
             *
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Character(
                IScene &scene,
                std::vector<std::string> tags = {"CHARACTER"});

            /**
             * @brief Destroy the Character object
             *
             */
            ~Character();

            /**
             * @brief Update the Character object
             *
             * @param delta Time since the last update
             */
            virtual void    update(float delta) override;

            /**
             * @brief If the Charcater still alive
             *
             * @return true The Character is alive
             * @return false The Character is not alive
             */
            virtual bool    isAlive(void) noexcept;

            /**
             * @brief Trigger the die animation of the Character
             *
             */
            virtual void    die(void) noexcept;

            const std::string &getUsername() const;

            void setUsername(const std::string &username);

    protected:
            bool    _isAlive;
            int     _timeAfterDie;
            std::string _username;

    };
}

#endif /* !CHARACTER_HPP_ */
