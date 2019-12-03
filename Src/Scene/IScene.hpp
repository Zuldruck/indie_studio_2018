/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** IScene.hpp
*/

#ifndef ISCENE_HPP
#define ISCENE_HPP


#include "Includes.hpp"
#include "EventReceiver.hpp"
#include "Core.hpp"

namespace ind {

    class IScene
    {
        public:
            virtual ~IScene() = default;

        /**
         * @brief Draw every objects in the scene using irrlicht drawAll. This method is called by the core every frame.
         * 
         */
        virtual void draw(float delta) noexcept = 0;
        /**
         * @brief Call update method of all objects in the scene, sending them delta. This method is called by the core every frame.
         * 
         * @param delta 
         */
        virtual void update(float delta) = 0;
        /**
         * @brief Call beginPlay method of all objects in the scene. This method is called by the core after the scene is fully loaded.
         * 
         */
        virtual void beginPlay(void) = 0;

        /**
         * @brief pause and unpuse the game
         * 
         */
        virtual void pause(void) = 0;

        /**
         * @brief return the Core associated with this scene.
         * 
         * @return Core&
         */
        virtual Core &getCore(void) noexcept = 0;
        /**
         * @brief Get the Input Receiver of this scene
         * 
         * @return std::unique_ptr<EventReceiver>& 
         */
        virtual std::unique_ptr<EventReceiver> &getEventReceiver(void) noexcept = 0;
        /**
         * @brief Get the Manager of this scene
         * 
         * @return irr::scene::ISceneManager* 
         */
        virtual irr::scene::ISceneManager *getManager(void) const noexcept = 0;
        /**
         * @brief Get the Collision Manager of this scene
         * 
         * @return std::shared_ptr<CollisionManager> 
         */
        virtual std::shared_ptr<CollisionManager> getCollisionManager(void) noexcept = 0;

        /**
         * @brief Get all the objects in the scene.
         * 
         * @return const std::vector<IObject_ptr>& 
         */
        virtual const std::vector<IObject_ptr> &getObjects(void) const noexcept = 0;
        /**
         * @brief Get all objects matching tag
         *
         * @param tag
         * @return std::vector<IObject_ptr>
         */
        virtual std::vector<IObject_ptr> getObjectsByTags(const std::string & tag) const noexcept = 0;
        /**
         * @brief Get the Object matching ID
         *
         * @param ID
         * @return IObject_ptr
         */
        virtual IObject_ptr getObjectByID(unsigned ID) const noexcept = 0;

        /**
         * @brief add an object to the scene. It will be added at the end of the update.
         * 
         * @param newObject 
         */
        virtual void addObject(IObject_ptr newObject) noexcept = 0;
        /**
         * @brief remove an object from the scene. It will be removed at the end of the update.
         * 
         * @param toRemove 
         */
        virtual void removeObject(IObject_ptr toRemove) noexcept = 0;
        /**
         * @brief remove an object from the scene. It will be removed at the end of the update.
         * 
         * @param toRemove 
         */
        virtual void removeObject(IObject *toRemove) noexcept = 0;


        protected:

        private:
    };

}

#endif /* !ISCENE_HPP */
