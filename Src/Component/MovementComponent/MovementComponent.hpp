/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** MovementComponent
*/

#ifndef MOVEMENTCOMPONENT_HPP_
#define MOVEMENTCOMPONENT_HPP_

#include "Component.hpp"

#define IDLE_OFFSET_MOVEMENT 0.01

namespace ind {
    class IObject;
    class AnimatedMeshComponent;
    class ParticleComponent;

    /**
     * @brief MovementComponent is a Class which update the position of an Object
     * 
     */
    class MovementComponent : public Component {
        public:
            /**
             * @brief Construct a new MovementComponent
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            MovementComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the MovementComponent
             * 
             */
            ~MovementComponent();


            /**
             * @brief Initialize the component before the start of the game
             * 
             */
            void    beginPlay(void) noexcept;

            /**
             * @brief Update the component
             * 
             * @param delta Time since the last update
             */
            void    update(float delta) noexcept;
            

            /**
             * @brief Update the position of the AmimatedMeshComponent linked to the owner of the component
             * 
             */
            void    updateMovement(void) noexcept;


            /**
             * @brief If the owner is moving
             * 
             * @return true The owner is moving
             * @return false The owner is motionless
             */
            bool    isMoving(void) noexcept;


            /**
             * @brief Set the Direction of the movement
             * 
             * @param direction Direction of the movement
             */
            void    setDirection(const irr::core::vector3df & direction) noexcept;

            /**
             * @brief Set the X axis of the Direction of the movement
             * 
             * @param directionX X axis of the Direction of the movement
             */
            void    setDirectionX(const float directionX) noexcept;

            /**
             * @brief Set the Y axis of the Direction of the movement
             * 
             * @param directionY Y axis of the Direction of the movement
             */
            void    setDirectionY(const float directionY) noexcept;

            /**
             * @brief Set the Z axis of the Direction of the movement
             * 
             * @param directionZ Z axis of the Direction of the movement
             */
            void    setDirectionZ(const float directionZ) noexcept;

            /**
             * @brief Set the Speed of the movement
             * 
             * @param speed Speed of the movement
             */
            void    setSpeed(const float speed) noexcept;


            /**
             * @brief Get the Direction of the movement
             * 
             * @return irr::core::vector3df Direction of the movement
             */
            irr::core::vector3df    getDirection(void) const noexcept;

            /**
             * @brief Get the Speed of the movement
             * 
             * @return float Speed of the movement
             */
            float                   getSpeed(void) const noexcept;


        private:
            float                                   _speed;
            irr::core::vector3df                    _direction;
            float                                   _idleOffsetMovement;

            std::shared_ptr<AnimatedMeshComponent>  _animatedMesh;
    };
}

#endif /* !MOVEMENTCOMPONENT_HPP_ */
