/*
** EPITECH PROJECT, 2018
** OOP_indie_studio_2018
** File description:
** GameScene.hpp
*/

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Includes.hpp"
#include "IScene.hpp"
#include "IObject.hpp"
#include "Map.hpp"
#include "ScoreManager.hpp"
#include "GameUI.hpp"
#include "MapBackground.hpp"
#include "GameLight.hpp"
#include "GameCamera.hpp"
#include "BombermanLobby.hpp"

namespace ind {

    class GameUI;

    class GameScene : public IScene
    {
    public:
        GameScene(Core &core);
        virtual ~GameScene();

        /**
         * @brief Draw every objects in the scene using irrlicht drawAll. This method is called by the core every frame.
         * 
         */
        virtual void draw(float delta) noexcept;

        /**
         * @brief Call update method of all objects in the scene, sending them delta. This method is called by the core every frame.
         * 
         * @param delta 
         */
        virtual void update(float delta);

        /**
         * @brief Call beginPlay method of all objects in the scene. This method is called by generateGame after the scene is fully generated.
         * 
         */
        virtual void beginPlay(void);

        /**
         * @brief pause and unpuse the game
         * 
         */
        virtual void pause(void);

        virtual void    generateGame() noexcept;
        /**
         * @brief Generate all the objects of the scene.
         * 
         */
        virtual void generateGame(std::vector<std::shared_ptr<BombermanLobby>> &settings) noexcept;

        /**
         * @brief return the Core associated with this scene.
         * 
         * @return Core&
         */
        virtual Core &getCore(void) noexcept;
        /**
         * @brief Get the Input Receiver of this scene
         * 
         * @return std::unique_ptr<EventReceiver>& 
         */
        virtual std::unique_ptr<EventReceiver> &getEventReceiver(void) noexcept;

        /**
         * @brief Get the Manager of this scene
         * 
         * @return irr::scene::ISceneManager* 
         */
        virtual irr::scene::ISceneManager *getManager(void) const noexcept;
        /**
         * @brief Get the Collision Manager of this scene
         * 
         * @return std::shared_ptr<CollisionManager> 
         */
        virtual std::shared_ptr<CollisionManager> getCollisionManager(void) noexcept;

        /**
         * @brief Get all the objects in the scene.
         * 
         * @return const std::vector<IObject_ptr>& 
         */
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

        /**
         * @brief add an object to the scene. It will be added at the end of the update.
         * 
         * @param newObject 
         */
        virtual void addObject(IObject_ptr newObject) noexcept;
        /**
         * @brief push every objects added to the scene in the objects vector. Called at the end of update.
         * 
         */
        virtual void pushObjects(void) noexcept;

        /**
         * @brief remove an object from the scene. It will be removed at the end of the update.
         *
         * @param toRemove
         */
        virtual void removeObject(IObject_ptr toRemove) noexcept;
        /**
         * @brief remove an object from the scene. It will be removed at the end of the update.
         *
         * @param toRemove
         */
        virtual void removeObject(IObject *toRemove) noexcept;
        /**
         * @brief clean every objects for which remove was asked. Called at the end of update.
         * 
         */
        virtual void cleanObjects(void) noexcept;

        unsigned int getNbPlayer() const;

        void setNbPlayer(unsigned int nbPlayer);

        const std::string &getUsername() const;

        void setUsername(const std::string &username);

        const std::shared_ptr<GameUI> &getGameUi() const;

        unsigned int getScorePlayer() const;

        void setScorePlayer(unsigned int scorePlayer);

        const std::shared_ptr<DjControl> &getEngineSound() const;

        void gameOver();
        bool isIsGameOver() const;

        std::vector<std::shared_ptr<BombermanLobby>> getSettings() const;

    protected:
        bool _paused = false;
        bool _hasStarted = false;
        Core &_core;
        irr::scene::ISceneManager *         _manager;
        irr::IrrlichtDevice *               _device;
        std::vector<IObject_ptr>            _objects;
        std::vector<IObject_ptr>            _removeObjects;
        std::vector<IObject_ptr>            _addObjects;
        std::vector<std::shared_ptr<BombermanLobby>>         _settings;

        std::unique_ptr<EventReceiver>      _evtReceiver;
        std::shared_ptr<CollisionManager>   _collisionManager;
        std::shared_ptr<DjControl>          _engineSound;
        std::shared_ptr<MapBackground>      _mapBackground;
        std::shared_ptr<Map>                _map;
        std::shared_ptr<GameLight>          _gameLight;
        std::shared_ptr<GameCamera>         _gameCamera;

        unsigned                            _IDs = 0;
        ScoreManager                        _scoreManager;
        unsigned int                        _scorePlayer;
        std::shared_ptr<GameUI>             _gameUI;
        unsigned int                        _nbPlayer = 1;
        std::string                         _username;
        bool                                _isGameOver;

    private:
    };
}

#endif /* !GAME_SCENE_HPP */
