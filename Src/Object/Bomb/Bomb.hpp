/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Object.hpp"
#include "Map.hpp"
#include "DjControl.hpp"

#define BOMB_ALIVE_TIME 1800

namespace ind {
    class BomberMan;

    /**
     * @brief Bomb are placed by a BomberMan.
     * They explode after a fixed time.
     * When they explode, they propagate Fire.
     * 
     */
    class Bomb : public Object {
        public:
            /**
             * @brief Construct a new Bomb object
             * 
             * @param scene The scene we will add this object
             * @param tags Tags that Fence object will have
             */
            Bomb(IScene &scene, std::vector<std::string> tags = {"BOMB"});

            /**
             * @brief Destroy the Bomb object
             * 
             */
            ~Bomb();

            /**
             * @brief Prepare all what we need for painless use this object
             * 
             */
            void                        beginPlay(void) noexcept;

            /**
             * @brief Update the bomb and trigger his explosion when timer ends
             * 
             * @param delta Time since the last update
             */
            void                        update(float delta) noexcept;

            /**
             * @brief Adapt a position to a Map's understandable position
             * For example, it tooks a bomberMan's position like [66.4, 12.56] and it returns [7, 1]
             * 
             * @param position Position to adapt
             * @return irr::core::vector3df Position adapted to the Map
             */
            irr::core::vector3df        adaptPositionToMap(irr::core::vector3df position) noexcept;

            /**
             * @brief Check if a Bomb can be placed to the actual position of the bomberMan which own the Bomb.
             * The postion must been EMPTY to be able to put a Bomb. 
             * 
             * @return true The position is empty and the Bomb can be placed
             * @return false The position is not empty and the Bomb canno't be placed
             */
            bool                        checkIfBombCanBePlaced(void) noexcept;

            /**
             * @brief Check if the a BomberMan is actually on the same position as the Bomb
             * 
             * @return true A Bomberman is actually on the bomb's position
             * @return false There is no bomberMan on the bomb's position
             */
            bool                        checkIfPlayerIsOnTheBomb(void) noexcept;

            /**
             * @brief Check all the Fire's position to know if the bomb's explosion have to propagate to this position
             * 
             * @param newFirePosition Position to check
             */
            void                        browseFires(irr::core::vector3df newFirePosition) noexcept;

            /**
             * @brief Check all the Bomb's position to know if the bomb's explosion have to trigger the explosion of another Bomb
             * 
             * @param newFirePosition Position to check
             */
            void                        browseBombs(irr::core::vector3df newFirePosition) noexcept;

            /**
             * @brief Check all the Boxes's position to know if the bomb's explosion have to destroy a Box
             * 
             * @param newFirePosition Position to check
             */
            void                        browseBoxes(irr::core::vector3df newFirePosition) noexcept;

            /**
             * @brief Call the constrcutor of a new Fire object and set it's position to the actual Map's Block.
             * 
             * @param actualBlock Actual Map's block onto create the new Fire object
             * @param newFirePosition New Fire's position
             */
            void                        createFire(Map::BlockType * actualBlock, irr::core::vector3df newFirePosition) noexcept;

            /**
             * @brief Check all the cases where a Fire object can be created
             * Create Fire if position is EMPTY and continue the propagation
             * Reset duration of Fire if position is FIRE and continue the propagation
             * Trigger the explosion of the Bomb if position is BOMB and stop the propagation
             * Destroy the Box if position is BOX and stop the propagation
             * 
             * @param actualBlock Actual Map's block onto create the new Fire object
             * @param newFirePosition New Fire's position
             * @return true The propagation continue in this direction
             * @return false The propagation stop in this direction
             */
            bool                        handleFireCases(Map::BlockType * actualBlock, irr::core::vector3df newFirePosition) noexcept;

            /**
             * @brief Browse all directions surrounding a Bomb to propagate the Fire
             * 
             */
            void                        propagateFire(void) noexcept;

            /**
             * @brief Set the BomberMan object which own the Bomb
             * 
             * @param bomberManOwner BomberMan object which own the Bomb
             */
            void                        setBomberManOwner(BomberMan * bomberManOwner) noexcept;

            /**
             * @brief Arm the bomb onto the ground
             * It also check if it can be placed
             * 
             */
            void                        arm(void) noexcept;

            /**
             * @brief Trigger the explosion of the Bomb
             * 
             * @param silentMode If the explosion propagate Fire or just desactivate the Bomb
             */
            void                        explode(bool silentMode) noexcept;

            /**
             * @brief Set the time to the Bomb to explode
             * 
             * @param aliveTime time to the Bomb to explode
             */
            void                        setAliveTime(float aliveTime) noexcept;

            /**
             * @brief Get the BomberMan object which own the Bomb
             * 
             * @return BomberMan* BomberMan object which own the Bomb
             */
            BomberMan *getBomberManOwner(void) noexcept;

            /**
             * @brief If the Bomb is armed on the ground
             * 
             * @return true The bomb is armed
             * @return false The bomb is not armed
             */
            bool                        isArm(void) const noexcept;

            /**
             * @brief Get the Position of the Bomb
             * 
             * @return irr::core::vector3df Position of the Bomb
             */
            irr::core::vector3df        getPosition(void) const noexcept;

        private:
            BomberMan *_bomberManOwner;
            std::shared_ptr<DjControl>  _engineSound;

            bool                        _isArm;
            float                       _aliveTime;
            irr::core::vector3df        _position;
    };
}

#endif /* !BOMB_HPP_ */
