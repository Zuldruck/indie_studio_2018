#include <utility>

/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include <utility>
#include "ControlKey.hpp"
#include "SoloMode.hpp"
#include "Principal.hpp"
#include "Settings.hpp"
#include "LoadGame.hpp"
#include "Credits.hpp"
#include "MultiPlayerMode.hpp"
#include <chrono>
#include <Src/Scene/MenuScene/MenuScene.hpp>
#include "GameScene.hpp"
#include "Menu.hpp"
#include "Lobby.hpp"
#include "Factory.hpp"
#include "GameCamera.hpp"


namespace ind {
    std::string _activeMenu = FIRSTSCENE;
    std::string temp = _activeMenu;

    ind::Menu::Menu(Core &core, bool firstTime) : _core(core)
    {
        /* save device and driver */
        _saveDevice = core.getDevice();
        _saveDriver = core.getDriver();
        _currentFrame = 0;
        _firstTime = firstTime;
        _usernameLoad = "Player";
        _levelLoad = 0;
        _scoreLoad = 0;
        _rangeLoad = 0;
        _speedLoad = 0;
        _bombLoad = 0;
        /* path to the root of the project */
        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* ENGINE SOUND CREATION */
        _engineSound = core.getEngineSound();

        if (!_engineSound)
            EXCEPTION(std::runtime_error, "_engineSound was null");

        _engineSound->playSong("soundMenu");
        _engineSound->controlVolumeSong("soundMenu", 20);
        _engineSound->playSong("seaSound");

        irr::scene::ICameraSceneNode *camera = _saveDevice->getSceneManager()->addCameraSceneNode(nullptr,
                                                                                                  irr::core::vector3df(-14.5f, 12, -13.0f),
                                                                                                  irr::core::vector3df(0, 0, 0), -1, true);
        camera->setTarget(irr::core::vector3df(5, 5, 0));

        // ------ LIGHT ------
        _saveDevice->getSceneManager()->setAmbientLight(irr::video::SColorf(0.3f, 0.3f, 0.3f, 1.0f));
        _saveDevice->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(-10, 30, 0.0f), irr::video::SColorf(0.8f, 0.8f, 0.8f, 1.0f));
        _saveDevice->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(0, 2, -15), irr::video::SColorf(0.1f, 0.1f, 0.1f, 1.0f));

        // ------ WATER ------
        irr::scene::IAnimatedMesh *meshWater = _saveDevice->getSceneManager()->getMesh(std::string(std::string(path) + "/Assets/lobby/water.b3d").c_str());
        irr::scene::ISceneNode *nodeWater = _saveDevice->getSceneManager()->addWaterSurfaceSceneNode(meshWater->getMesh(0), 0.04f, 300.0f, 30.0f);
        nodeWater->setPosition(irr::core::vector3df(-13, -1.6f, -0.3f));
        nodeWater->setMaterialTexture(0, _saveDriver->getTexture(std::string(std::string(path) + "/Assets/lobby/water.png").c_str()));

        // ------ MAP ------
        irr::scene::IAnimatedMesh *meshMap = _saveDevice->getSceneManager()->getMesh(std::string(std::string(path) + "/Assets/lobby/lobby.3ds").c_str());
        _meshNodeMap =
                _saveDevice->getSceneManager()->addAnimatedMeshSceneNode(meshMap,  0, -1,
                                                                         irr::core::vector3df(0.5f, 0.0f, 0.3f),
                                                                         irr::core::vector3df(0.0f, 0.0f, 0.0f));
        _meshNodeMap->setMaterialFlag(irr::video::EMF_LIGHTING, true);

        /* LOBBY CREATION */
        for (irr::u32 idx = 0; idx < 4; idx++)
            this->createBomberman(idx + 1);

        /* CREATION OF THE SUB MENU */
        _sceneMenu.insert(std::make_pair("principal", std::make_shared<Principal>(Principal(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("settings",  std::make_shared<Settings>(Settings(_core, _saveDevice, _engineSound, _saveDriver))));
        _sceneMenu.insert(std::make_pair("loadGame",  std::make_shared<LoadGame>(LoadGame(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("credits",  std::make_shared<Credits>(Credits(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("soloMode",  std::make_shared<SoloMode>(SoloMode(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("controlKey",  std::make_shared<ControlKey>(ControlKey(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("multiPlayerMode",  std::make_shared<MultiPlayerMode>(MultiPlayerMode(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("lobby",  std::make_shared<Lobby>(Lobby(_saveDevice, _saveDriver, camera, _vectBomberman))));

        /* SAVE SCREEN SIZE */
        _saveScreenSize.set(1920, 1080);

        /* Splash Screen + Introduction */
        if (!_firstTime)
            _activeMenu = "quit_intro";
    }

    ind::Menu::~Menu()
    {
        _engineSound->stopSong("soundMenu");
        _engineSound->stopSong("seaSound");
    }

    void ind::Menu::createBomberman(irr::u32 idx)
    {
        std::shared_ptr<BombermanLobby> bomberman = std::make_shared<BombermanLobby>(idx, _saveDevice, _saveDriver);
        this->_vectBomberman.push_back(bomberman);
    }

    void ind::Menu::draw(float delta)
    {
        if (_currentFrame > MAX_FRAME_INTRO || _activeMenu == "quit_intro") {
            if (_activeMenu == "quit_intro") {
                _activeMenu = "principal";
                _currentFrame = MAX_FRAME_INTRO + 1;
            }
            _saveDevice->getSceneManager()->drawAll();

            for (const auto &elem : _sceneMenu) {
                if (_core.isLoadRequested()) {

                    prepareLoadGame();
                    if (_runLoad) {
                        _core.loadGame(_usernameLoad, _levelLoad, _scoreLoad, _speedLoad, _rangeLoad, _bombLoad);
                        return;
                    }
                }
                if (temp != _activeMenu) {
                    /* sound that play a button clicked sound effect */
                    _engineSound->playSong("buttonClicked");

                    /* detect if we need to switch into the game with solo or multi */
                    if (this->detectSoloMultiMode())
                        return;

                    /* clear environment */
                    _saveDevice->getGUIEnvironment()->clear();

                    /* This part will try if a new scene are request, if it is it will clear the last one and show the new scene requested */
                    this->showAndRunScene();
                }
                if (elem.second->isActive())
                    elem.second->drawGUi(delta);
            }
        } else {
            playVideo(delta);
        }
    }

    void ind::Menu::playVideo(float delta)
    {
        irr::video::ITexture * textureVideo = nullptr;
    
        if (this->_currentFrame < 10)
            textureVideo = _saveDriver->getTexture(std::string(std::string(this->path) + "/Assets/animation/_00" + std::to_string(this->_currentFrame) + ".jpg").c_str());
        else if (this->_currentFrame >= 10 && this->_currentFrame < 100)
            textureVideo = _saveDriver->getTexture(std::string(std::string(this->path) + "/Assets/animation/_0" + std::to_string(this->_currentFrame) + ".jpg").c_str());
        else
            textureVideo = _saveDriver->getTexture(std::string(std::string(this->path) + "/Assets/animation/_" + std::to_string(this->_currentFrame) + ".jpg").c_str());
        _saveDriver->draw2DImage(textureVideo, irr::core::position2d<irr::s32>(0, 0),
                                 irr::core::rect<irr::s32>(0, 0, 1920, 1080), 0,
                                 irr::video::SColor(255,255,255,255), true);
        this->_currentFrame++;
    }

    bool Menu::detectSoloMultiMode()
    {
        unsigned nbPlayer = 0;

        if (_activeMenu == "gameScene") {

            /* sound that play a button clicked sound effect */
            _engineSound->playSong("buttonClicked");
            _activeMenu = "soloMode";

            auto soloModeScene = _sceneMenu.find("soloMode")->second;
            auto saveUsername = soloModeScene->getUsername();
            nbPlayer = 1;
            auto gameScene = std::make_shared<GameScene>(_core);
            this->createUIForNPlayers(gameScene, nbPlayer, saveUsername);
            _core.loadScene(gameScene);
            return true;
        } else if (_activeMenu == "multiPlayerMode") {
            /* sound that play a button clicked sound effect */
            _engineSound->playSong("buttonClicked");
            auto gameScene = std::make_shared<GameScene>(_core);
            for (auto &i: _vectBomberman) {
                if (i->getPlayerMode() != "NONE")
                    nbPlayer += 1;
            }
            this->createUIForNPlayers(gameScene, nbPlayer);
            _core.loadScene(gameScene);
            return true;
        }
        return false;
    }

    void Menu::showAndRunScene()
    {
        if (_sceneMenu.find(_activeMenu) != _sceneMenu.end()) {
            auto tempScene = ind::Menu::findWithExcept<std::shared_ptr<IMenu>>(
                    _sceneMenu, _activeMenu,
                    std::string(_activeMenu + " can not be find"));

            tempScene->cleanScope();
            tempScene->setActive(true);
            tempScene->createGUI(_saveDevice, _saveDriver);
            temp = _activeMenu;
        } else {
            EXCEPTION(std::runtime_error,
                      "Error when trying to open " + _activeMenu +
                      " menu.");
        }
    }


    void Menu::createUIForNPlayers(std::shared_ptr<ind::GameScene> gameScene, unsigned int numberPlayer, const std::string& username)
    {
        if (numberPlayer > 4 || numberPlayer < 1)
            EXCEPTION(std::runtime_error, "You can't play a game with more than 4 players or less than one.");
        clean();

        if (numberPlayer == 1) {
            _core.setCurrentLevel(1);
            gameScene->setNbPlayer(1);
            gameScene->generateGame(_vectBomberman);
            gameScene->setUsername(username);
            gameScene->getGameUi()->createStyleUI(1);
            gameScene->getGameUi()->createTimer(120000);
            gameScene->getGameUi()->createScore();
        }

        if (numberPlayer == 2) {
            gameScene->setNbPlayer(2);
            gameScene->generateGame(_vectBomberman);
            gameScene->setUsername("Player1");
            gameScene->getGameUi()->createStyleUI(1);
            gameScene->setUsername("Player2");
            gameScene->getGameUi()->createStyleUI(2);
            gameScene->getGameUi()->createScore();
        }

        if (numberPlayer == 3) {
            gameScene->setNbPlayer(3);
            gameScene->generateGame(_vectBomberman);
            gameScene->setUsername("Player1");
            gameScene->getGameUi()->createStyleUI(1);
            gameScene->setUsername("Player2");
            gameScene->getGameUi()->createStyleUI(2);
            gameScene->setUsername("Player3");
            gameScene->getGameUi()->createStyleUI(3);
            gameScene->getGameUi()->createScore();
        }

        if (numberPlayer == 4) {
            gameScene->setNbPlayer(4);
            gameScene->generateGame(_vectBomberman);
            gameScene->setUsername("Player1");
            gameScene->getGameUi()->createStyleUI(1);
            gameScene->setUsername("Player2");
            gameScene->getGameUi()->createStyleUI(2);
            gameScene->setUsername("Player3");
            gameScene->getGameUi()->createStyleUI(3);
            gameScene->setUsername("Player4");
            gameScene->getGameUi()->createStyleUI(4);
            gameScene->getGameUi()->createScore();
        }
    }

    void Menu::clean()
    {
        if (_meshNodeMap)
            _meshNodeMap->remove();
        _saveDevice->getGUIEnvironment()->clear();
    }

    void Menu::prepareLoadGame()
    {
        auto indexItemSelected = 0;
        std::string dataItemSelected;

        auto loadScene = _sceneMenu.find("loadGame")->second;

        if (!loadScene)
            EXCEPTION(std::runtime_error, "loadGame Scene was null");

        auto loadSceneWithCast = std::static_pointer_cast<LoadGame>(loadScene);
        auto listGameSaved= loadSceneWithCast->getMapExtra().find<irr::gui::IGUIListBox *>("listGameSaved");

        if (!listGameSaved)
            EXCEPTION(std::runtime_error, "listGameSaved was not found.");

        if ((indexItemSelected = listGameSaved->getSelected()) != -1) {
            const wchar_t* txt = listGameSaved->getListItem(indexItemSelected);
            std::wstring ws(txt);
            std::string str(ws.begin(), ws.end());

            dataItemSelected = str;

            if (dataItemSelected.find("Level:") != std::string::npos) {
                _usernameLoad = dataItemSelected.substr(0, dataItemSelected.find("Level:"));
                _usernameLoad = _usernameLoad.substr(_usernameLoad.find(':') + 1);
                epur(_usernameLoad);
            } else
                std::cout << "ERROR PARSE USERNAME." << std::endl;

            if (dataItemSelected.find("Score:") != std::string::npos) {
                std::string tempLevel(dataItemSelected.substr(dataItemSelected.find("Level:") + 6));
                std::string resLevel(tempLevel.substr(0, tempLevel.find("Score:")));

                epur(resLevel);
                _levelLoad = std::atoi(resLevel.data());
            } else
                std::cout << "ERROR PARSE LEVEL." << std::endl;

            if (dataItemSelected.find("Score:") != std::string::npos) {
                std::string resScore(dataItemSelected.substr(dataItemSelected.find("Score:") + 6));

                epur(resScore);
                _scoreLoad = std::atoi(resScore.data());
            } else
                std::cout << "ERROR PARSE SCORE." << std::endl;

            if (dataItemSelected.find("Speed:") != std::string::npos) {
                std::string temp(dataItemSelected.substr(dataItemSelected.find("Speed:") + 6));
                std::string resSpeed(temp.substr(0, temp.find("Range:")));

                epur(resSpeed);
                _speedLoad = std::atoi(resSpeed.data());
            }

            if (dataItemSelected.find("Range:") != std::string::npos) {
                std::string temp(dataItemSelected.substr(dataItemSelected.find("Range:") + 6));
                std::string resRange(temp.substr(0, temp.find("Bomb:")));

                epur(resRange);
                _rangeLoad = std::atoi(resRange.data());
            }

             if (dataItemSelected.find("Bomb:") != std::string::npos) {
                std::string resRange(dataItemSelected.substr(dataItemSelected.find("Bomb:") + 6));

                epur(resRange);
                _bombLoad = std::atoi(resRange.data());
            }


            _runLoad = true;
        } else {
            _runLoad = false;
        }
    }

    void Menu::createLobbySolo()
    {
        /*  LOBBY CREATION */

        _saveDevice->getSceneManager()->addCameraSceneNode(nullptr, irr::core::vector3df(-14.5f, 12, -13.0f),irr::core::vector3df(0, 5, -2), -1, true);

        // ------ LIGHT ------
        _saveDevice->getSceneManager()->setAmbientLight(irr::video::SColorf(0.3f, 0.3f, 0.3f, 1.0f));
        _saveDevice->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(-10, 30, 0.0f), irr::video::SColorf(0.8f, 0.8f, 0.8f, 1.0f));
        _saveDevice->getSceneManager()->addLightSceneNode(nullptr, irr::core::vector3df(0, 2, -15), irr::video::SColorf(0.1f, 0.1f, 0.1f, 1.0f));

        // ------ WATER ------
        irr::scene::IAnimatedMesh *meshWater = _saveDevice->getSceneManager()->getMesh(std::string(std::string(path) + "/Assets/lobby/water.b3d").c_str());
        irr::scene::ISceneNode *nodeWater = _saveDevice->getSceneManager()->addWaterSurfaceSceneNode(meshWater->getMesh(0), 0.04f, 300.0f, 30.0f);
        nodeWater->setPosition(irr::core::vector3df(-13, -1.6f, -0.3f));
        nodeWater->setMaterialTexture(0, _saveDriver->getTexture(std::string(std::string(path) + "/Assets/lobby/water.png").c_str()));

        // ------ MAP ------
        irr::scene::IAnimatedMesh *meshMap = _saveDevice->getSceneManager()->getMesh(std::string(std::string(path) + "/Assets/lobby/lobby.3ds").c_str());
        _meshNodeMap =
                _saveDevice->getSceneManager()->addAnimatedMeshSceneNode(meshMap,  0, -1,
                                                                         irr::core::vector3df(0.5f, 0.0f, 0.3f),
                                                                         irr::core::vector3df(0.0f, 0.0f, 0.0f));
        _meshNodeMap->setMaterialFlag(irr::video::EMF_LIGHTING, true);

        /* CREATION OF THE SUB MENU */
        _sceneMenu.insert(std::make_pair("principal", std::make_shared<Principal>(Principal(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("settings",  std::make_shared<Settings>(Settings(_core, _saveDevice, _engineSound, _saveDriver))));
        _sceneMenu.insert(std::make_pair("loadGame",  std::make_shared<LoadGame>(LoadGame(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("credits",  std::make_shared<Credits>(Credits(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("soloMode",  std::make_shared<SoloMode>(SoloMode(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("controlKey",  std::make_shared<ControlKey>(ControlKey(_core, _saveDevice, _saveDriver))));
        _sceneMenu.insert(std::make_pair("multiPlayerMode",  std::make_shared<MultiPlayerMode>(MultiPlayerMode(_core, _saveDevice, _saveDriver))));

        /* SAVE SCREEN SIZE */
        _saveScreenSize.set(1920, 1080);
    }

    irr::video::ITexture *
    ind::Menu::getTextureWithExcept(irr::video::IVideoDriver *driver, const std::string& path, const std::string& errorMessage)
    {
        if (!driver)
            EXCEPTION(std::runtime_error, "driver variable given in args are null.");
        if (path.empty() || errorMessage.empty())
            EXCEPTION(std::runtime_error, "path or errorMessage are empty.");
        auto obj = driver->getTexture(path.c_str());

        if (!obj)
            EXCEPTION(std::runtime_error, errorMessage);
        return (obj);
    }

    void Menu::epur(std::string &s)
    {
        bool space = false;
        auto p = s.begin();
        for (auto ch : s)
            if (std::isspace(ch)) {
                space = p != s.begin();
            } else {
                if (space) *p++ = ' ';
                *p++ = ch;
                space = false; }
        s.erase(p, s.end());

    }

    const boost::unordered_map<std::string, std::shared_ptr<IMenu>> &Menu::getSceneMenu() const
    {
        return _sceneMenu;
    }

    ind::EventReceiverMenu::EventReceiverMenu(Core &core, std::shared_ptr<DjControl> _engineSound) : _core(core)
    {
        _saveDevice = _core.getDevice();
        _saveEngineSound = std::move(_engineSound);
    }

    bool ind::EventReceiverMenu::OnEvent(const irr::SEvent &event)
    {
        if (event.KeyInput.Key == irr::KEY_F4)
            _core.stop();
        if (event.EventType == irr::EET_KEY_INPUT_EVENT && _activeMenu == "principal")
            if (event.KeyInput.Key == irr::KEY_SPACE)
                _activeMenu = "quit_intro";

        if (event.EventType == irr::EET_GUI_EVENT) {

            ind::ind_int id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType) {

                case irr::gui::EGET_EDITBOX_ENTER:
                {
                    if (!std::dynamic_pointer_cast<MenuScene>(_core.getScene()))
                        break;
                    auto soloModeScene = std::static_pointer_cast<SoloMode>(std::static_pointer_cast<MenuScene>(_core.getScene())->getMainMenu()->getSceneMenu().find("soloMode")->second);
                    if (soloModeScene->getUsername() == "ENTER YOUR USERNAME" || soloModeScene->getUsername().empty() || soloModeScene->getUsername() == "ENTER CORRECT NAME") {
                        soloModeScene->setUsername("ENTER CORRECT NAME");
                        break;
                    }
                    _activeMenu = "gameScene";
                }
                    break;

                case irr::gui::EGET_EDITBOX_MARKING_CHANGED:
                {
                    if (!std::dynamic_pointer_cast<MenuScene>(_core.getScene()))
                        break;
                    auto soloModeScene = std::static_pointer_cast<SoloMode>(std::static_pointer_cast<MenuScene>(_core.getScene())->getMainMenu()->getSceneMenu().find("soloMode")->second);
                    if (soloModeScene->getUsername() == "ENTER YOUR USERNAME" || soloModeScene->getUsername() == "ENTER CORRECT NAME")
                        soloModeScene->setUsername("");
                }
                    break;
                case irr::gui::EGET_SCROLL_BAR_CHANGED:
                    if (id == GUI_ID_VOLUME_SCROLL_BAR) {
                        ind::ind_int pos = static_cast<irr::gui::IGUIScrollBar *>(event.GUIEvent.Caller)->getPos();
                        if (_saveEngineSound != nullptr)
                            _saveEngineSound->controlVolumeSong("soundMenu", pos);
                        else
                            std::cout << "ERRROR ENGINE SOUND WAS NULL" << std::endl;
                    }
                    break;

                case irr::gui::EGET_BUTTON_CLICKED:
                    switch(id)
                    {
                        case GUI_ID_QUIT_BUTTON:
                            _saveDevice->closeDevice();
                            return true;

                        case GUI_ID_RUN_SETTINGS:
                        {
                            _activeMenu = "settings";
                        }
                            return true;

                        case GUI_ID_RUN_LOAD:
                        {
                            _activeMenu = "loadGame";
                        }
                            return true;

                        case GUI_ID_RUN_LOAD_GAME:
                        {
                            _core.setLoadRequested(true);
                        }
                            return true;

                        case GUI_ID_RUN_PRINCIPAL:
                        {
                            _activeMenu = "principal";
                        }
                            return true;
                        case GUI_ID_RUN_CONTROL_KEY:
                        {
                            _activeMenu = "controlKey";
                        }
                            return true;

                        case GUI_ID_RUN_MULTI:
                        {
                            _activeMenu = "lobby";
                        }
                            return true;

                        case GUI_ID_RUN_CREDITS:
                        {
                            _activeMenu = "credits";
                        }
                            return true;

                        case GUI_ID_RUN_SOLO:
                        {
                            _activeMenu = "soloMode";
                        }
                            return true;

                        case GUI_ID_RUN_PLAY:
                        {
                            if (!std::dynamic_pointer_cast<MenuScene>(_core.getScene()))
                                break;
                            auto soloModeScene = std::static_pointer_cast<SoloMode>(std::static_pointer_cast<MenuScene>(_core.getScene())->getMainMenu()->getSceneMenu().find("soloMode")->second);
                            if (soloModeScene->getUsername().empty()
                            || soloModeScene->getUsername() == "ENTER CORRECT NAME"
                            || soloModeScene->getUsername() == "ENTER YOUR USERNAME") {
                                soloModeScene->setUsername("ENTER CORRECT NAME");
                                break;
                            }
                            _activeMenu = "gameScene";
                        }
                            return true;
                        case GUI_ID_RUN_PLAY_MULTI:
                        {
                            _activeMenu = "multiPlayerMode";
                        }
                            return true;

                        default:
                            return false;
                    }
                    break;
                default:
                    break;
            }
        }

        return false;
    }

}
