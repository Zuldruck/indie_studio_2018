/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** CollisionManager
*/

#ifndef COLLISIONMANAGER_HPP_
#define COLLISIONMANAGER_HPP_

#include "Includes.hpp"
#include "PlayerCollisionComponent.hpp"
#include "MonsterCollisionComponent.hpp"

namespace ind {
    class Core;
    class IObject;

    /**
     * @brief CollisionManager hangles collisions in games.
     * 
     */
    class CollisionManager {
        public:
            /**
             * @brief Construct a new Collision Manager object
             * 
             * @param scene 
             */
            CollisionManager(irr::scene::ISceneManager * scene = nullptr);
            /**
             * @brief Destroy the Collision Manager object
             * 
             */
            ~CollisionManager();

            /**
             * @brief used to link object to the collision manager.
             * 
             */
            void    beginPlay(void) noexcept;

            /**
             * @brief create and add a static collision from the component to the manager
             * 
             * @param component 
             */
            void    addStaticCollision(irr::scene::IAnimatedMeshSceneNode * mesh) noexcept;

            /**
             * @brief create and add a Dynamic collision from the component to the manager. It's meant for player because radius is reduced.
             * 
             * @param component 
             */
            void    addPlayerCollision(irr::scene::IAnimatedMeshSceneNode * mesh, PlayerCollisionComponent *comp) noexcept;

            /**
             * @brief create and add a Dynamic collision from the component to the manager. It's meant for monsters.
             * 
             * @param component 
             */
            void    addMonsterCollision(irr::scene::IAnimatedMeshSceneNode * mesh, MonsterCollisionComponent *comp) noexcept;


            /**
             * @brief remove a collision from the manager
             * 
             * @param component 
             */
            void removeCollision(irr::scene::ITriangleSelector *triangle) noexcept;
            /**
             * @brief put back a collision to the manager. Is often called by activate methods of component.
             * 
             * @param component 
             */
            void addCollision(irr::scene::ITriangleSelector *triangle) noexcept;

        protected:
            irr::scene::ISceneManager *         _scene;
            irr::scene::IMetaTriangleSelector * _metaSelector;
        private:
    };
}

#endif /* !COLLISIONMANAGER_HPP_ */
