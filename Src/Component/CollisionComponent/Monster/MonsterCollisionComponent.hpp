/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** MonsterCollisionComponent
*/

#ifndef MONSTERCOLLISIONCOMPONENT_HPP_
#define MONSTERCOLLISIONCOMPONENT_HPP_

#include "CollisionComponent.hpp"

namespace ind {

    /**
     * @brief MonsterCollisionComponent is a Class which handle the collisions of Mobs
     * 
     */
    class MonsterCollisionComponent : public Component, public irr::scene::ICollisionCallback {
        public:
            /**
             * @brief Construct a new MonsterCollisionComponent
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            MonsterCollisionComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the MonsterCollisionComponent
             * 
             */
            virtual ~MonsterCollisionComponent();

            /**
             * @brief Trigger when a Mob collide a StaticCollisionComponent
             * 
             * @param animator Animator which collide. It contains the collided node and the collider node
             * @return true Do not check collisions anymore
             * @return false Still check collisions
             */
            virtual bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);

            /**
             * @brief Get the AnimatedMeshComponent associated
             * 
             * @return std::shared_ptr<AnimatedMeshComponent>& AnimatedMeshComponent associated
             */
            std::shared_ptr<AnimatedMeshComponent> &getMeshComponent(void) noexcept;

        protected:
            std::shared_ptr<AnimatedMeshComponent> _meshComponent;
    };
}

#endif /* !MONSTERCOLLISIONCOMPONENT_HPP_ */
