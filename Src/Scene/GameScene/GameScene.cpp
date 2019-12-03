/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** GameScene
*/

#include "GameScene.hpp"
#include "BomberMan.hpp"
#include "Factory.hpp"
#include "Wall.hpp"
#include "AnimatedMeshComponent.hpp"
#include "Player.hpp"
#include "Bomber.hpp"
#include "Blob.hpp"
#include "Leeroy.hpp"
#include "BombermanLobby.hpp"

namespace ind {
    GameScene::GameScene(Core &core) : _core(core)
    {
        std::string path = getcwd(nullptr, 0);

        _manager = core.getDevice()->getSceneManager();
        _device = core.getDevice();
        _collisionManager = std::make_shared<CollisionManager>(_manager);
        _evtReceiver = std::make_unique<EventReceiver>(*this);
        _engineSound = _core.getEngineSound();
        _core.setLoadRequested(false);
        _scoreManager = ind::ScoreManager();
        _scoreManager.setDevice(_device);

#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        _engineSound->playSong("gameMusic");
        _isGameOver = false;

    }

    GameScene::~GameScene()
    {
        _engineSound->stopSong("gameMusic");
        if (_addObjects.empty() == false) {
            pushObjects();
        }
        if (_removeObjects.empty() == false) {
            cleanObjects();
        }
        _objects.clear();
    }

    void    GameScene::generateGame() noexcept
    {
        _mapBackground = Factory::createObject<MapBackground>(*this);
        _map = Factory::createObject<Map>(*this);
        _gameLight = Factory::createObject<GameLight>(*this);
        _gameCamera = Factory::createObject<GameCamera>(*this);

        _scorePlayer = 0;
        _gameUI = std::make_shared<GameUI>(GameUI(this));
        beginPlay();
    }

    void    GameScene::generateGame(std::vector<std::shared_ptr<BombermanLobby>> &settings) noexcept
    {
        _settings = settings;
        _mapBackground = Factory::createObject<MapBackground>(*this);
        _map = Factory::createObject<Map>(*this);
        _gameLight = Factory::createObject<GameLight>(*this);
        _gameCamera = Factory::createObject<GameCamera>(*this);

        _scorePlayer = 0;
        _gameUI = std::make_shared<GameUI>(GameUI(this));
        beginPlay();
    }
    
    void                                GameScene::beginPlay(void)
    {
        _collisionManager->beginPlay();
        _evtReceiver->setJoysticks(_device);
        BOOST_FOREACH(IObject_ptr &obj, _objects)
                        obj->beginPlay();
        _hasStarted = true;
    }

    void                                GameScene::draw(float delta) noexcept
    {
        _manager->drawAll();
        _manager->getGUIEnvironment()->drawAll();
    }

    void                                GameScene::update(float delta)
    {
        if (_paused)
            return;
        if (_gameUI->update())
            gameOver();
        BOOST_FOREACH(IObject_ptr &object, _objects) {
            object->update(delta);
        }
        if (!_addObjects.empty())
            pushObjects();
        if (_removeObjects.empty() == false) {
            cleanObjects();
        }

    }

    void GameScene::pause(void)
    {
        if (_paused == false) {
            _paused = true;
        } else {
            _paused = false;
        }
        BOOST_FOREACH(IObject_ptr &obj, _objects)
                        obj->pause();
        _gameUI->pauseAndGameOverUI();
    }

    Core &GameScene::getCore(void) noexcept
    {
        return _core;
    }

    std::unique_ptr<EventReceiver> &    GameScene::getEventReceiver(void) noexcept
    {
        return _evtReceiver;
    }

    irr::scene::ISceneManager *         GameScene::getManager(void) const noexcept
    {
        return _manager;
    }

    std::shared_ptr<CollisionManager>   GameScene::getCollisionManager(void) noexcept
    {
        return _collisionManager;
    }

    const std::vector<IObject_ptr > &   GameScene::getObjects(void) const noexcept
    {
        return _objects;
    }

    std::vector<IObject_ptr >           GameScene::getObjectsByTags(const std::string &tag) const noexcept
    {
        std::vector<IObject_ptr > objects;

        for (auto &obj : _objects) {
            if (obj->hasTag(tag)) {
                objects.push_back(obj);
            }
        }
        return objects;
    }

    void                                GameScene::addObject(IObject_ptr newObject) noexcept
    {
        if (!_hasStarted) {
            _objects.push_back(newObject);
        } else {
            _addObjects.push_back(newObject);
        }
        newObject->setId(_IDs);
        _IDs++;
    }

    void GameScene::pushObjects(void) noexcept
    {

        BOOST_FOREACH(auto &e, _addObjects) {
                        _objects.push_back(e);
                        if (_hasStarted)
                            e->beginPlay();
                    }
        _addObjects.clear();
    }

    void                                GameScene::removeObject(IObject_ptr toRemove) noexcept
    {
        for (auto it = _objects.begin(); it != _objects.end(); it++) {
            if (it->get() == toRemove.get()) {
                _removeObjects.push_back(toRemove);
                break;
            }
        }
    }

    void                                GameScene::removeObject(IObject *toRemove) noexcept
    {
        int index = 0;

        for (auto it = _objects.begin(); it != _objects.end(); it++, index++) {
            if (it->get() == toRemove) {
                _removeObjects.push_back(_objects[index]);
                break;
            }
        }
    }

    IObject_ptr                         GameScene::getObjectByID(unsigned ID) const noexcept
    {
        for (auto &obj : _objects)
            if (obj->getId() == ID)
                return (obj);
        return nullptr;
    }

    void GameScene::cleanObjects(void) noexcept
    {
        auto itFirst = _objects.begin();
        auto itLast = _objects.end();

        for (auto it = _removeObjects.begin(); it != _removeObjects.end(); it++) {
            _objects.erase(std::find(itFirst, itLast, *it));
        }
        _removeObjects.clear();
    }

    unsigned int GameScene::getNbPlayer() const
    {
        return _nbPlayer;
    }

    void GameScene::setNbPlayer(unsigned int nbPlayer)
    {
        _nbPlayer = nbPlayer;
    }

    const std::string &GameScene::getUsername() const
    {
        return _username;
    }

    void GameScene::setUsername(const std::string &username)
    {
        _username = username;
    }

    const std::shared_ptr<GameUI> &GameScene::getGameUi() const {
        return _gameUI;
    }

    unsigned int GameScene::getScorePlayer() const
    {
        return _scorePlayer;
    }

    void GameScene::setScorePlayer(unsigned int scorePlayer)
    {
        _scorePlayer = scorePlayer;
    }

    const std::shared_ptr<DjControl> &GameScene::getEngineSound() const
    {
        return _engineSound;
    }

    void GameScene::gameOver()
    {
        _scoreManager.addScore(getUsername(), getScorePlayer());
        _scoreManager.saveOnFile();
        _engineSound->stopSong("gameMusic");
        _isGameOver = true;

        pause();
    }

    bool GameScene::isIsGameOver() const
    {
        return _isGameOver;
    }

    std::vector<std::shared_ptr<BombermanLobby>> GameScene::getSettings() const
    {
        return _settings;
    }

}
