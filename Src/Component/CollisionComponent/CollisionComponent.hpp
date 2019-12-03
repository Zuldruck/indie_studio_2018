/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CollisionComponent
*/

#ifndef COLLISIONCOMPONENT_HPP_
#define COLLISIONCOMPONENT_HPP_

#include "Component.hpp"
#include "AnimatedMeshComponent.hpp"

namespace ind  {
    class IObject;

    /**
     * @brief StaticCollisionComponent added a static collision to an object. It can't detect other collider but dynamics detect it.
     * 
     */
    class StaticCollisionComponent : public Component {
        public:
            /**
             * @brief Construct a new Static Collision Component object
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            StaticCollisionComponent(IObject *owner, bool isActivated = true);
            /**
             * @brief Destroy the Static Collision Component object
             * 
             */
            virtual ~StaticCollisionComponent();

            /**
             * @brief Get the Mesh Component associated
             * 
             * @return std::shared_ptr<AnimatedMeshComponent>& 
             */
            std::shared_ptr<AnimatedMeshComponent> &getMeshComponent(void) noexcept;
            /**
             * @brief Activate the collision.
             * 
             */
            virtual void    activate(void) noexcept;
            /**
             * @brief Desactivate the collision.
             * 
             */
            virtual void    desactivate(void) noexcept;

        protected:
            std::shared_ptr<AnimatedMeshComponent> _meshComponent;
    };

    /**
     * @brief MobStaticCollisionComponent add a second static collision to an object which carry it's own AnimatedMeshSceneNode and is placed under the main AnimatedMeshComponent
     * 
     */
    class MobStaticCollisionComponent : public Component {
        public:
            /**
             * @brief Construct a new MobStaticCollisionComponent 
             * 
             * @param owner Object which own the component
             * @param isActivated If the component is activate by default
             */
            MobStaticCollisionComponent(IObject *owner, bool isActivated = true);

            /**
             * @brief Destroy the MobStaticCollisionComponent
             * 
             */
            virtual ~MobStaticCollisionComponent();

            /**
             * @brief Update the MobStaticCollisionComponent by replacing it's AnimatedMeshSceneNode to the owner's AnimatedMeshComponent position
             * 
             * @param delta Time since the last update in milliseconds
             */
            void    update(float delta) noexcept;
        
        protected:
            irr::scene::IAnimatedMeshSceneNode *    _mesh;
    };
}

#endif /* !COLLISIONCOMPONENT_HPP_ */
