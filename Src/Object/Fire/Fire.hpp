/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Fire
*/

#ifndef FIRE_HPP_
#define FIRE_HPP_

#include "Object.hpp"

#define FIRE_ALIVE_TIME 700

namespace ind {
    class Map;

    /**
     * @brief Fire is propagated by Bomb's explosion.
     * It kills Player and Mobs
     * It destroy Boxes
     * 
     */
    class Fire : public Object {
        public:

            /**
             * @brief Construct a new Fire object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Fire(IScene &scene, std::vector<std::string> tags = {"FIRE"});

            /**
             * @brief Destroy the Fire object
             * 
             */
            ~Fire() = default;

            /**
             * @brief Update the Fire object.
             * If it's timer ends, the fire goes out
             * 
             * @param delta Time since the last update
             */
            void    update(float delta) noexcept;

            /**
             * @brief Extinguish the fire qnd delete the object
             * 
             */
            void    extinguish(void) noexcept;

            /**
             * @brief Reset the timer of the Fire object
             * 
             */
            void    resetAliveTime(void) noexcept;

            /**
             * @brief Set the Position of the Fire object
             * 
             * @param position Position of the Fire object
             */
            void    setPosition(irr::core::vector3df position) noexcept;

            /**
             * @brief Set the duration of the Fire object
             * 
             * @param aliveTime duration of the Fire object
             */
            void    setAliveTime(float aliveTime) noexcept;
            
            /**
             * @brief Get the Position of the Fire object
             * 
             * @return irr::core::vector3df Position of the Fire object
             */
            irr::core::vector3df    getPosition(void) const noexcept;
        
        private:
            std::shared_ptr<Map>    _map;

            irr::core::vector3df    _position;
            float                   _aliveTime;
    };
}

#endif /* !FIRE_HPP_ */
