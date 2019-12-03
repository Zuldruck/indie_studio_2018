/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** Core
*/

#include <MenuScene.hpp>
#include "MovementComponent.hpp"
#include "Core.hpp"
#include "Factory.hpp"
#include "IObject.hpp"
#include "EventReceiver.hpp"
#include "CollisionManager.hpp"
#include "Map.hpp"
#include "BomberMan.hpp"
#include "GameScene.hpp"

namespace ind {

    Core::Core() : _currentLevel(1)
    {
        _device = irr::createDevice(
                VIDEO_MODE,
                irr::core::dimension2d<irr::u32>(WINDOW_WIDTH, WINDOW_HEIGHT),
                32, true, true, false);
        _device->getLogger()->setLogLevel(irr::ELL_ERROR);
        _driver = _device->getVideoDriver();
        _persistantData.setDevice(_device);
        _loadRequested = false;
        _saveScore = 0;

        char *cPath = getcwd(nullptr, 0);
        std::string _path(cPath);
        #ifdef __APPLE__
            _path += "/OOP_indie_studio_2018";
        #endif /* !__APPLE__ */

        _engineSound = std::make_shared<DjControl>();
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/bombDeposited.wav", "bombDeposited");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/explosion.wav", "bombExplosion");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/fire.wav", "fireWave");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/sound_menu.wav", "soundMenu");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/buttonClicked.wav", "buttonClicked");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/scrolling.wav", "scrolling");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/seaSound.wav", "seaSound");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/ingame.wav", "gameMusic");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/death.wav", "death");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/gameOver.wav", "gameOver");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/bonus.wav", "bonus");
        _engineSound->addSong(std::string(_path) + "/Assets/sounds/teleportation.wav", "teleportation");
        _engineSound->controlVolumeSong("bombDeposited", 30);
        _engineSound->controlVolumeSong("fireWave", 50);
        _engineSound->setLoopToASong("gameMusic");
        _engineSound->setLoopToASong("soundMenu");
        _engineSound->setLoopToASong("seaSound");
        free(cPath);
        _device->activateJoysticks(_joysticks);
    }

    void Core::setLoadRequested(bool loadRequested)
    {
        _loadRequested = loadRequested;
    }

    bool Core::isLoadRequested() const
    {
        return _loadRequested;
    }

    Core::~Core()
    {
        _scene.reset();
        _device->drop();
    }

    void Core::saveGame() const
    {
        std::string username = dynamic_cast<GameScene*>(_scene.get())->getUsername();
        std::string score = std::to_string(dynamic_cast<GameScene*>(_scene.get())->getScorePlayer());
        std::string level = std::to_string(_currentLevel);
        std::string bonusString = "";

        if (_scene->getObjectsByTags("PLAYER").size() != 1) {
            _persistantData.putRawDataOnFile("games.data", username + ":" + level + ";" + score + "\n", true);
            return;
        }

        BomberMan *bomberman = static_cast<BomberMan*>(_scene->getObjectsByTags("PLAYER")[0].get());
        bonusString += "speed:";
        bonusString += std::to_string(bomberman->getBonusSpeed());
        bonusString += ";range:";
        bonusString += std::to_string(bomberman->getBonusRange());
        bonusString += ";bomb:";
        bonusString += std::to_string(bomberman->getBonusBomb());
        _persistantData.putRawDataOnFile("games.data", username + ':' + level + ';' + score + '|' + bonusString + '\n', true);
    }

    template <>
    std::shared_ptr<GameScene> Core::loadScene<GameScene>(void)
    {
        _scene.reset();
        _scene = std::make_shared<GameScene>(*this);

        _device->setEventReceiver(_scene->getEventReceiver().get());

        return (std::dynamic_pointer_cast<GameScene>(_scene));
    }

    template <>
    std::shared_ptr<MenuScene> Core::loadScene<MenuScene>(bool firstTime)
    {
        _scene.reset();
        _scene = std::make_shared<MenuScene>(*this, firstTime);
        return (std::dynamic_pointer_cast<MenuScene>(_scene));
    }

    template <>
    void Core::loadScene<MenuScene>(std::shared_ptr<MenuScene> scene)
    {
        _scene.reset();
        _scene = scene;
    }

    template <>
    void Core::loadScene<GameScene>(std::shared_ptr<GameScene> scene)
    {
        _scene.reset();

        _device->setEventReceiver(scene->getEventReceiver().get());
        _scene = scene;
    }

    void                                Core::setCurrentLevel(unsigned int currentLevel) noexcept
    {
        _currentLevel = currentLevel;
    }

    unsigned int                        Core::getCurrentLevel(void) const noexcept
    {
        return _currentLevel;
    }

    void                                Core::setUp(void)
    {
        this->loadScene<MenuScene>(true);
    }

    void                                Core::update(void)
    {
        auto start = _device->getTimer()->getTime();
        auto delta = start;

        while (_device->run() && _driver) {
            delta = _device->getTimer()->getTime() - start;
            if (delta >= 1000.0 / _fps) {
                _scene->update(delta);
                _driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
                _scene->draw(delta);
                _driver->endScene();
                start = _device->getTimer()->getTime();
            }
        }
    }

    void                                Core::draw()
    {
        auto start = _device->getTimer()->getTime();
        auto delta = start;

        while (_device->run() && _driver) {
            delta = _device->getTimer()->getTime() - start;
            if (delta >= 1000.0 / _fps) {
                _driver->beginScene(true, true, irr::video::SColor(255,255,255,255));
                _scene->draw(delta);
                _driver->endScene();
                start = _device->getTimer()->getTime();
            }
        }


    }

    void                                Core::run(void)
    {
        this->update();
    }

    void                                Core::stop(void) noexcept
    {
        _device->closeDevice();
    }

    irr::video::IVideoDriver *          Core::getDriver(void) const noexcept
    {
        return _driver;
    }

    irr::IrrlichtDevice *Core::getDevice(void) const noexcept
    {
        return _device;
    }

    const std::shared_ptr<IScene> &Core::getScene() const
    {
        return _scene;
    }

    const std::shared_ptr<DjControl> &Core::getEngineSound() const
    {
        return _engineSound;
    }

    std::vector<std::string> Core::getSaveGame()
    {
        std::vector<std::string> segList;
        std::string segment;
        std::string dataFile = _persistantData.readRawDataFromFile("games.data");
        std::stringstream data(dataFile);
        while(std::getline(data, segment, '\n'))
            segList.push_back(segment);
        return segList;
    }

    irr::core::array<irr::SJoystickInfo> Core::getJoysticks(void) const
    {
        return _joysticks;
    }

    void Core::loadGame(const std::string& username, unsigned int level, unsigned int score,
                        unsigned int speed, unsigned int range, unsigned int bomb)
    {
        unsigned nbPlayer = 1;
        _saveUsername = username;
        _saveScore = score;

        std::static_pointer_cast<MenuScene>(_scene)->getMainMenu()->clean();
        auto gameScene = loadScene<GameScene>();
        setCurrentLevel(level);
        gameScene->setNbPlayer(nbPlayer);
        gameScene->generateGame();
        gameScene->setScorePlayer(_saveScore);
        gameScene->setUsername(_saveUsername);

        auto player = gameScene->getObjectsByTags("PLAYER")[0];
        std::static_pointer_cast<BomberMan>(player)->setBonusBomb(bomb);
        std::static_pointer_cast<BomberMan>(player)->setBonusRange(range);
        std::static_pointer_cast<BomberMan>(player)->setBonusSpeed(speed);
        gameScene->getGameUi()->createScore();
        gameScene->getGameUi()->createStyleUI(1);
        gameScene->getGameUi()->createPowerUPUI(1);
        gameScene->getGameUi()->createTimer(120000);
    }

}
