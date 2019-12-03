/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include "Lobby.hpp"
#include "BomberMan.hpp"
#include "Factory.hpp"
#include "Object.hpp"
#include "AnimatedMeshComponent.hpp"
#include "MovementComponent.hpp"
#include "Bomber.hpp"
#include "IScene.hpp"
#include "Player.hpp"
#include "GameUI.hpp"
#include <functional>
#include <unordered_map>

namespace ind {

    Lobby::~Lobby() = default;

    Lobby::Lobby(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
            irr::scene::ICameraSceneNode *camera, std::vector<std::shared_ptr<BombermanLobby>> vectBomberman) : _receiverLobby(device) {
        /* init new sceneManaer */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _lobbySceneManager = temp->createNewSceneManager(false);

        if (_lobbySceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _lobbySceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* init to default the attributes */
        _saveDevice = device;
        _saveDriver = driver;
        _lobbyCamera = camera;
        _vectBomberman = vectBomberman;

        _active = false;
        _hoverBack = false;
        _hoverPlay = false;
        _hoverPrev = false;
        _hoverNext = false;
        _hoverChooseType = false;

        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_back.png"),
                                                           "btn_back can't be found.");
        auto backTextureHover = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");
        auto playTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_play.png"),
                                                           "btn_play can't be found.");
        auto playHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_play_hover.png"), "btn_play_hover can't be found.");
        auto prevTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/arrow-left.png"),
                                                           "btn_prev can't be found.");
        auto prevHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/lobby/arrow-left.png"), "btn_prev_hover can't be found.");
        auto nextTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/arrow-right.png"),
                                                           "btn_next can't be found.");
        auto nextHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/lobby/arrow-right.png"), "btn_next_hover can't be found.");
        auto backgroundPlayerNameTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/bg_player.png"),
                                                           "bg_player can't be found.");
        auto backgroundSkinTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/bg2_skin.png"),
                                                                           "bg2_skin can't be found.");
        auto background1SkinTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/bg1_skin.png"),
                                                                     "bg1_skin can't be found.");
        auto btnModeTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/btnMode.png"),
                                                           "btnMode can't be found.");
        auto btnModeHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/lobby/btnModeHover.png"), "btnModeHover can't be found.");
        auto btnSkinBlueTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/bleu.png"),
                                                              "btnSkinBlue can't be found.");
        auto btnSkinWhiteTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/white.png"),
                                                                  "btnSkinWhite can't be found.");
        auto btnSkinBlackTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/black.png"),
                                                                   "btnSkinBlack can't be found.");
        auto btnSkinYellowTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/yellow.png"),
                                                                   "btnSkinYellow can't be found.");
        auto btnSkinRedTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/lobby/red.png"),
                                                                    "btnSkinRed can't be found.");

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backTextureHover));
        _mapTextures.insert(std::make_pair("play", playTexture));
        _mapTextures.insert(std::make_pair("playHover", playHoverTexture));
        _mapTextures.insert(std::make_pair("prev", prevTexture));
        _mapTextures.insert(std::make_pair("prevHover", prevHoverTexture));
        _mapTextures.insert(std::make_pair("next", nextTexture));
        _mapTextures.insert(std::make_pair("nextHover", nextHoverTexture));
        _mapTextures.insert(std::make_pair("backgroundPlayerNameTexture", backgroundPlayerNameTexture));
        _mapTextures.insert(std::make_pair("backgroundSkinTexture", backgroundSkinTexture));
        _mapTextures.insert(std::make_pair("background1SkinTexture", background1SkinTexture));
        _mapTextures.insert(std::make_pair("btnMode", btnModeTexture));
        _mapTextures.insert(std::make_pair("btnModeHover", btnModeHoverTexture));
        _mapTextures.insert(std::make_pair("btnSkinBlueTexture", btnSkinBlueTexture));
        _mapTextures.insert(std::make_pair("btnSkinWhiteTexture", btnSkinWhiteTexture));
        _mapTextures.insert(std::make_pair("btnSkinBlackTexture", btnSkinBlackTexture));
        _mapTextures.insert(std::make_pair("btnSkinYellowTexture", btnSkinYellowTexture));
        _mapTextures.insert(std::make_pair("btnSkinRedTexture", btnSkinRedTexture));

        _positionCamera = -1;
        _mapBtnAction["back"] = &Lobby::setMovementCameraMenu;
        _mapBtnAction["prev"] = &Lobby::setMovementCameraPrev;
        _mapBtnAction["next"] = &Lobby::setMovementCameraNext;
        _mapBtnAction["btnMode"] = &Lobby::setModePlayer;
        _mapBtnAction["btnSkinBlue"] = &Lobby::setPlayerSkinBlue;
        _mapBtnAction["btnSkinWhite"] = &Lobby::setPlayerSkinWhite;
        _mapBtnAction["btnSkinBlack"] = &Lobby::setPlayerSkinBlack;
        _mapBtnAction["btnSkinYellow"] = &Lobby::setPlayerSkinYellow;
        _mapBtnAction["btnSkinRed"] = &Lobby::setPlayerSkinRed;
        _lobbyIsActive = false;
        _nextIsActive = false;
        _prevIsActive = false;

    }

    void Lobby::drawGUi(float delta) {
        if (_activeMenu != "lobby" && isActive())
            setActive(false);
        if (_lobbyIsActive == false)
            this->setMovementCameraMenuToLobby(delta);
        else {
            this->updateGUI(delta);
            _lobbySceneManager->drawAll();
            _guiScene->drawAll();
        }
    }

    bool Lobby::isActive() const {
        return _active;
    }

    void Lobby::setActive(bool _active) {
        Lobby::_active = _active;
    }

    void Lobby::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(&_receiverLobby);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void Lobby::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* textures find */
        auto backgroundPlayerNameTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backgroundPlayerNameTexture",
                                                                                             "backgroundPlayerNameTexture texture are not found");
        auto backgroundSkinTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backgroundSkinTexture",
                                                                                       "backgroundSkinTexture texture are not found");
        auto background1SkinTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "background1SkinTexture",
                                                                                        "background1SkinTexture texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("backgroundPlayerNameTexture",
                                         _guiScene->addImage(backgroundPlayerNameTexture, irr::core::position2d<int>(width / 2 - 253, 240))));
        _mapImages.insert(std::make_pair("backgroundSkinTexture",
                                         _guiScene->addImage(backgroundSkinTexture, irr::core::position2d<int>(width / 2 + 200, 600))));
        _mapImages.insert(std::make_pair("background1SkinTexture",
                                         _guiScene->addImage(background1SkinTexture, irr::core::position2d<int>(width / 2 + 200, 410))));
    }

    void Lobby::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("play", _guiScene->addButton(
                irr::core::rect<ind_int>(width - (192 * 2), height - 100, width,
                                         height - 100 + 93), 0, GUI_ID_RUN_PLAY_MULTI,
                L"", L"Run multiplayer game")));
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height - 100, (192 * 2),
                                         height - 100 + 93), 0, GUI_ID_RUN_PRINCIPAL,
                L"", L"Return to the main menu")));
        _mapButtons.insert(std::make_pair("prev", _guiScene->addButton(
                irr::core::rect<ind_int>(100, height / 2 - 50, 200,
                                         height / 2 + 50), 0, GUI_ID_LOBBY_PREV,
                L"", L"Precedent Bomberman")));
        _mapButtons.insert(std::make_pair("next", _guiScene->addButton(
                irr::core::rect<ind_int>(width - 200, height / 2 - 50, width - 100,
                                         height / 2 + 50), 0, GUI_ID_LOBBY_NEXT,
                L"", L"Next Bomerman")));
        _mapButtons.insert(std::make_pair("btnMode", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 200, height / 2 - 245, width / 2 - 150,
                                         height / 2 - 195), 0, GUI_ID_LOBBY_MODE_PLAYER,
                L"", L"Change mode player")));
        _mapButtons.insert(std::make_pair("btnSkinBlue", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 300, height / 2 + 150, width / 2 + 330,
                                         height / 2 + 180), 0, GUI_ID_LOBBY_SKIN_BLUE,
                L"", L"Skin Blue")));

        _mapButtons.insert(std::make_pair("btnSkinWhite", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 360, height / 2 + 150, width / 2 + 390,
                                         height / 2 + 180), 0, GUI_ID_LOBBY_SKIN_WHITE,
                L"", L"Skin Default")));
        _mapButtons.insert(std::make_pair("btnSkinBlack", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 420, height / 2 + 150, width / 2 + 450,
                                         height / 2 + 180), 0, GUI_ID_LOBBY_SKIN_BLACK,
                L"", L"Skin Black")));
        _mapButtons.insert(std::make_pair("btnSkinYellow", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 480, height / 2 + 150, width / 2 + 530,
                                         height / 2 + 180), 0, GUI_ID_LOBBY_SKIN_YELLOW,
                L"", L"Skin Yellow")));
        _mapButtons.insert(std::make_pair("btnSkinRed", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 540, height / 2 + 150, width / 2 + 580,
                                         height / 2 + 180), 0, GUI_ID_LOBBY_SKIN_RED,
                L"", L"Skin Jordan")));

        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                            "back button are not found");
        auto playButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "play",
                                                                            "play button are not found");
        auto prevButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "prev",
                                                                            "prev button are not found");
        auto nextButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "next",
                                                                            "next button are not found");
        auto modeButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnMode",
                                                                            "mode button are not found");
        auto skinBlueButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnSkinBlue",
                                                                                "skinBlueButton button are not found");
        auto skinWhiteButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnSkinWhite",
                                                                                 "skinWhiteButton button are not found");
        auto skinBlackButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnSkinBlack",
                                                                                 "skinBlackButton button are not found");
        auto skinYellowButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnSkinYellow",
                                                                                  "skinYellowButton button are not found");
        auto skinRedButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnSkinRed",
                                                                               "skinRedButton button are not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                             "back texture are not found");
        auto playTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "play",
                                                                             "play texture are not found");
        auto prevTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "prev",
                                                                             "prev texture are not found");
        auto nextTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "next",
                                                                             "next texture are not found");
        auto modeTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnMode",
                                                                             "next texture are not found");
        auto skinBlueTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnSkinBlueTexture",
                                                                                 "skinBlue texture are not found");
        auto skinWhiteTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnSkinWhiteTexture",
                                                                                  "skinWhite texture are not found");
        auto skinBlackTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnSkinBlackTexture",
                                                                                  "skinBlack texture are not found");
        auto skinYellowTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnSkinYellowTexture",
                                                                                   "skinYellow texture are not found");
        auto skinRedTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnSkinRedTexture",
                                                                                "skinRed texture are not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
        playButton->setImage(playTexture);
        prevButton->setImage(prevTexture);
        prevButton->setDrawBorder(false);
        prevButton->setUseAlphaChannel(true);
        nextButton->setImage(nextTexture);
        nextButton->setDrawBorder(false);
        nextButton->setUseAlphaChannel(true);
        modeButton->setImage(modeTexture);
        modeButton->setDrawBorder(false);
        modeButton->setUseAlphaChannel(true);
        skinBlueButton->setImage(skinBlueTexture);
        skinWhiteButton->setImage(skinWhiteTexture);
        skinBlackButton->setImage(skinBlackTexture);
        skinYellowButton->setImage(skinYellowTexture);
        skinRedButton->setImage(skinRedTexture);
    }

    void Lobby::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        _mapTexts.insert(std::make_pair("playerName",
                                        _guiScene->addStaticText(L"PLAYER 1",
                                                                 irr::core::rect<ind_int>(width / 2 - 110, height / 2 - 260, width / 2 + 310, height / 2 + 80), false)));
        _mapTexts.insert(std::make_pair("skinText",
                                        _guiScene->addStaticText(L"SKIN",
                                                                 irr::core::rect<ind_int>(width / 2 + 380, height / 2 - 90, width / 2 + 500, height / 2 + 20), false)));

        auto textP1 = _mapTexts.find("playerName");
        auto textSkin = _mapTexts.find("skinText");

        textP1->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textP1->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
        textSkin->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textSkin->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));    }

    void Lobby::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void Lobby::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
    }

    void Lobby::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "lobby") {
            if (_receiverLobby.getBtnClick() != "none") {
                auto it = _mapBtnAction.begin();
                for (; it != _mapBtnAction.end(); it++) {
                    if (_receiverLobby.getBtnClick() == it->first) {
                        (this->*(it->second))(delta);
                        _receiverLobby.setBtnClick("none");
                    }
                }
            }
            if (_prevIsActive)
                setMovementCameraPrev(delta);
            else if (_nextIsActive)
                setMovementCameraNext(delta);

            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back button are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                                 "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover",
                                                                                      "backHover texture are not found");

            auto playButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "play",
                                                                                "play button are not found");
            auto playTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "play",
                                                                                 "play texture are not found");
            auto playHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "playHover",
                                                                                      "playHover texture are not found");


            auto arrowButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "btnMode",
                                                                                "game button are not found");
            auto arrowTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnMode",
                                                                                 "play texture btnMode not found");
            auto arrowHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "btnModeHover",
                                                                                      "btnModeHover texture are not found");

            /* play with these Assets */
            if (!_hoverBack &&
                backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                backButton->setImage(backHoverTexture);
                _hoverBack = true;
            } else if (_hoverBack && !backButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverBack = false;
                backButton->setImage(backTexture);
            }
            if (!_hoverPlay &&
                playButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                playButton->setImage(playHoverTexture);
                _hoverPlay = true;
            } else if (_hoverPlay && !playButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverPlay = false;
                playButton->setImage(playTexture);
            }
            if (!_hoverChooseType &&
                arrowButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                arrowButton->setImage(arrowHoverTexture);
                _hoverChooseType = true;
            } else if (_hoverChooseType && !playButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverChooseType = false;
                arrowButton->setImage(arrowTexture);
            }
        }
    }

    std::string Lobby::getUsername()
    {
        return ("");
    }

    void Lobby::setMovementCameraMenuToLobby(float delta)
    {
        if (_activeMenu == "lobby") {
            if (_lobbyCamera->getPosition().X < - 1) {
                _lobbyCamera->setTarget(irr::core::vector3df(1.5f, 1, 10));
                _lobbyCamera->setPosition(irr::core::vector3df(
                        _lobbyCamera->getPosition().X + ((0.06f * 1.7f) / 10) * delta,
                        _lobbyCamera->getPosition().Y - ((0.046f * 1.7f) / 10) * delta,
                        _lobbyCamera->getPosition().Z + ((0.009f * 1.7f) / 10) * delta));
            } else
                _lobbyIsActive = true;
        }
    }

    void Lobby::setMovementCameraMenu(float delta)
    {
        _lobbyCamera->setPosition(irr::core::vector3df(-14.5f, 12, -13.0f));
        _lobbyCamera->setTarget(irr::core::vector3df(5, 5, 0));
        _lobbyIsActive = false;
        _activeMenu = "principal";
    }

    void Lobby::setMovementCameraPrev(float delta)
    {
        if (_nextIsActive == false && _positionCamera != -1) {
            if (_lobbyCamera->getPosition().X > _positionCamera - 2.5f) {
                _lobbyCamera->setPosition(irr::core::vector3df(
                        _lobbyCamera->getPosition().X - (0.06f / 10) * delta,
                        _lobbyCamera->getPosition().Y,
                        _lobbyCamera->getPosition().Z));
                _lobbyCamera->setTarget(irr::core::vector3df(_positionCamera - 2.5f, 1, 10));
                _prevIsActive = true;
            } else {
                setPlayerNameText(getBomermanView() - 1);
                _prevIsActive = false;
                _positionCamera -= 2.5f;
            }
        }
    }

    void Lobby::setMovementCameraNext(float delta)
    {
        if (_prevIsActive == false && _positionCamera != 6.5f) {
            if (_lobbyCamera->getPosition().X < _positionCamera + 2.5f) {
                _lobbyCamera->setPosition(irr::core::vector3df(
                        _lobbyCamera->getPosition().X + (0.06f / 10) * delta,
                        _lobbyCamera->getPosition().Y,
                        _lobbyCamera->getPosition().Z));
                _lobbyCamera->setTarget(irr::core::vector3df(_positionCamera + 2.5f, 1, 10));
                _nextIsActive = true;
            } else {
                setPlayerNameText(getBomermanView() + 1);
                _nextIsActive = false;
                _positionCamera += 2.5f;
            }
        }
    }

    int Lobby::getBomermanView()
    {
        int bombermanView = 0;

        if (_positionCamera == -1)
            bombermanView = 0;
        else if (_positionCamera == 1.5f)
            bombermanView = 1;
        else if (_positionCamera == 4)
            bombermanView = 2;
        else
            bombermanView = 3;
        return bombermanView;
    }

    void Lobby::setPlayerNameText(int idx)
    {
        irr::gui::IGUIStaticText *textPlayer = _mapTexts.find("playerName")->second;

        textPlayer->setText(ind::GameUI::convertStringToWchar(_vectBomberman[idx]->getPlayerName()).data());
    }

    void Lobby::setModePlayer(float delta)
    {
        if (_vectBomberman[getBomermanView()]->getPlayerMode().compare("PLAYER") == 0) {
            _vectBomberman[getBomermanView()]->setPlayerMode("IA");
        } else if (_vectBomberman[getBomermanView()]->getPlayerMode().compare("IA") == 0){
            _vectBomberman[getBomermanView()]->setPlayerMode("NONE");
        } else {
            _vectBomberman[getBomermanView()]->setPlayerMode("PLAYER");
        }
        setPlayerNameText(getBomermanView());
    }

    void Lobby::setPlayerSkinBlue(float delta)
    {
        _vectBomberman[getBomermanView()]->setPlayerTexture("blue");
    }

    void Lobby::setPlayerSkinWhite(float delta)
    {
        _vectBomberman[getBomermanView()]->setPlayerTexture("default");
    }

    void Lobby::setPlayerSkinBlack(float delta)
    {
        _vectBomberman[getBomermanView()]->setPlayerTexture("black");
    }

    void Lobby::setPlayerSkinYellow(float delta)
    {
        _vectBomberman[getBomermanView()]->setPlayerTexture("yellow");
    }

    void Lobby::setPlayerSkinRed(float delta)
    {
        _vectBomberman[getBomermanView()]->setPlayerTexture("red");
    }

    EventReceiverLobby::EventReceiverLobby (irr::IrrlichtDevice *device)
    {
        _saveDevice = device;
        _btnClick = "none";
    }

    bool ind::EventReceiverLobby::OnEvent(const irr::SEvent &event)
    {
        if (event.EventType == irr::EET_GUI_EVENT) {
            ind::ind_int id = event.GUIEvent.Caller->getID();

            switch(event.GUIEvent.EventType) {
                case irr::gui::EGET_BUTTON_CLICKED:
                    switch(id)
                    {
                        case GUI_ID_RUN_PRINCIPAL:
                        {
                            this->_btnClick = "back";
                        }
                            return true;

                        case GUI_ID_RUN_PLAY_MULTI:
                        {
                            _activeMenu = "multiPlayerMode";
                        }
                            return true;

                        case GUI_ID_LOBBY_PREV:
                        {
                            this->_btnClick = "prev";
                        }
                            return true;

                        case GUI_ID_LOBBY_NEXT:
                        {
                            this->_btnClick = "next";
                        }
                            return true;
                        case GUI_ID_LOBBY_MODE_PLAYER:
                        {
                            this->_btnClick = "btnMode";
                        }
                            return true;
                        case GUI_ID_LOBBY_SKIN_BLUE:
                        {
                            this->_btnClick = "btnSkinBlue";
                        }
                            return true;
                        case GUI_ID_LOBBY_SKIN_WHITE:
                        {
                            this->_btnClick = "btnSkinWhite";
                        }
                            return true;
                        case GUI_ID_LOBBY_SKIN_BLACK:
                        {
                            this->_btnClick = "btnSkinBlack";
                        }
                            return true;
                        case GUI_ID_LOBBY_SKIN_YELLOW:
                        {
                            this->_btnClick = "btnSkinYellow";
                        }
                            return true;
                        case GUI_ID_LOBBY_SKIN_RED:
                        {
                            this->_btnClick = "btnSkinRed";
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