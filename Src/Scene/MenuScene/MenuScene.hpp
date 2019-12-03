/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_MENUSCENE_HPP
#define BOMBERMAN_MENUSCENE_HPP


#include <Menu/Menu.hpp>
#include "Includes.hpp"
#include "IScene.hpp"
#include "IObject.hpp"

namespace ind {

    class MenuScene : public IScene
    {
    public:
        MenuScene(Core &core, bool firstTime = true);
        virtual ~MenuScene();

        virtual void draw(float delta) noexcept;
        virtual void update(float delta);
        virtual void beginPlay(void);
        /**
         * @brief pause and unpuse the game
         * 
         */
        virtual void pause(void);

        virtual Core &getCore(void) noexcept;
        virtual std::unique_ptr<EventReceiver> &getEventReceiver(void) noexcept;

        virtual irr::scene::ISceneManager *getManager(void) const noexcept;
        virtual std::shared_ptr<CollisionManager> getCollisionManager(void) noexcept;

        virtual const std::vector<IObject_ptr> &getObjects(void) const noexcept;
        /**
         * @brief Get all objects matching tag
         *
         * @param tag
         * @return std::vector<IObject_ptr>
         */
        virtual std::vector<IObject_ptr> getObjectsByTags(const std::string & tag) const noexcept;
        /**
         * @brief Get the Object matching ID
         *
         * @param ID
         * @return IObject_ptr
         */
        virtual IObject_ptr getObjectByID(unsigned ID) const noexcept;

        virtual void addObject(IObject_ptr newObject) noexcept;
        virtual void removeObject(IObject_ptr toRemove) noexcept;
        virtual void removeObject(IObject *toRemove) noexcept;

        void generateLobby(void);

        const std::unique_ptr<Menu> &getMainMenu() const;

    protected:
        Core &_core;
        irr::scene::ISceneManager *         _manager;
        std::vector<IObject_ptr>            _objects;
        std::unique_ptr<EventReceiver>      _evtReceiver;
        std::shared_ptr<CollisionManager>   _collisionManager;
        irr::scene::ICameraSceneNode *      _camera;
        std::unique_ptr<Menu> 				_mainMenu;

        unsigned                            _IDs = 0;
        bool                                _firstTime;

    private:
    };
}


#endif //BOMBERMAN_MENUSCENE_HPP
