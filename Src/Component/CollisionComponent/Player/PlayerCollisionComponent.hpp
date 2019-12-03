/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** PlayerCollisionComponent
*/

#ifndef PLAYERCOLLISIONCOMPONENT_HPP_
#define PLAYERCOLLISIONCOMPONENT_HPP_

#include "CollisionComponent.hpp"

namespace ind
{
    /**
     * @brief PlayerCollisionComponent is a component that added a dynamic collision to an object. It implement onCollision method, called when a collision occured.
     * 
     */
    class PlayerCollisionComponent : public Component, public irr::scene::ICollisionCallback {
        public:
        /**
         * @brief Construct a new Player Collision Component object
         * 
         * @param owner Object which own the component
         * @param isActivated If the component is activate by default
         */
            PlayerCollisionComponent(IObject *owner, bool isActivated = true);
            virtual ~PlayerCollisionComponent();
            /**
             * @brief onCollision method is inherited from irr::scene::ICollisionCallback. It is called when a collision occured, and animator gives every info from both object nodes.
             * 
             * @param animator 
             * @return true 
             * @return false 
             */
            virtual bool onCollision(const irr::scene::ISceneNodeAnimatorCollisionResponse &animator);
            
            /**
             * @brief Get the Mesh Component assiociated.
             * 
             * @return std::shared_ptr<AnimatedMeshComponent>& 
             */
            std::shared_ptr<AnimatedMeshComponent> &getMeshComponent(void) noexcept;

        protected:
            std::shared_ptr<AnimatedMeshComponent>  _meshComponent;

            int                                     _offsetY;
    };
}

#endif /* !PLAYERCOLLISIONCOMPONENT_HPP_ */
