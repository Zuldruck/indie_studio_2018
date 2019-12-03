/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "LoadGame.hpp"

namespace ind {
    LoadGame::~LoadGame() {}

    LoadGame::LoadGame(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) : _receiver(core), _core(core) {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _loadSceneManager = temp->createNewSceneManager(false);

        if (_loadSceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _loadSceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* init to default the attributes */
        _saveDevice = device;
        _saveDriver = driver;

        _active = false;

        _hoverBack = false;
        _hoverGo = false;

        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_back.png"),
                                                           "btn_back can't be found.");
        auto backHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");
        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/logo.png"),
                                                           "logo can't be found.");
        auto goTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_go.png"),
                                                         "btn_go can't be found.");
        auto goHoverTexture = ind::Menu::getTextureWithExcept(driver,
                                                              std::string(path + "/Assets/menu/btn_go_hoover.png"),
                                                              "btn_go_hoover can't be found.");
        auto bgLoad = ind::Menu::getTextureWithExcept(driver,
                                                      std::string(path + "/Assets/UI/bgLoad.png"),
                                                      "bgLoad can't be found.");

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backHoverTexture));
        _mapTextures.insert(std::make_pair("logo", logoTexture));
        _mapTextures.insert(std::make_pair("go", goTexture));
        _mapTextures.insert(std::make_pair("goHover", goHoverTexture));
        _mapTextures.insert(std::make_pair("bgLoad", bgLoad));
    }

    void LoadGame::drawGUi(float delta) {
        if (_activeMenu != "loadGame" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _loadSceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool LoadGame::isActive() const
    {
        return _active;
    }

    void LoadGame::setActive(bool active)
    {
        LoadGame::_active = active;
    }

    void LoadGame::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(&_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void LoadGame::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo",
                                                                             "logo texture not found");
        auto bgLoad = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgLoad",
                                                                        "bgLoad texture not found");
        /* init trivial variables */
        auto width = 	device->getVideoDriver()->getScreenSize().Width;


        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10, 10))));


        /* find textures */
        _mapImages.insert(std::make_pair("bgLoad", _guiScene->addImage(bgLoad, irr::core::position2d<int>(width / 2 - 500, logoTexture->getSize().Height + 15))));
    }

    void LoadGame::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 200 - 192, height / 2 + 250, width / 2 - 200 + 192,
                                         height / 2 + 250 + 93), 0, GUI_ID_RUN_PRINCIPAL,
                L"", L"Return to the main menu")));

        _mapButtons.insert(std::make_pair("go", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 + 200 - 192, height / 2 + 250, width / 2 + 200 + 192,
                                         height / 2 + 250 + 93), 0, GUI_ID_RUN_LOAD_GAME,
                L"", L"Return to the main menu")));

        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                            "back button not found");
        auto goButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "go", "go button not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                             "back texture not found");
        auto goTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "go", "go texture not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
        goButton->setImage(goTexture);
    }

    void LoadGame::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;

        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo", "logo texture not found");

        /* INIT TEXTS */
        _mapTexts.insert(std::make_pair("chooseTexts",
                                        _guiScene->addStaticText(L"CHOOSE A SAVED GAME AND GO:",
                                                                 irr::core::rect<ind_int>( width / 2 - 480,
                                                                                           logoTexture->getSize().Height - 50,
                                                                                           width / 2 + 500,
                                                                                           740),
                                                                 false)));

        auto textVolume =  ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "chooseTexts", "error when trying to get the volumeLabel texts");
        textVolume->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textVolume->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

    }

    void LoadGame::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        /* init trivial variables */
        unsigned index = 0;
        std::string res;
        auto width = 	device->getVideoDriver()->getScreenSize().Width;

        /* find textures */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo", "logo texture not found");

        /* add extra */
        _mapExtra.insert<irr::gui::IGUIListBox *>("listGameSaved", _guiScene->addListBox(irr::core::rect<ind_int>
                                                                                                 (
                                                                                                         width / 2 - 485,
                                                                                                         logoTexture->getSize().Height + 25,
                                                                                                         width / 2 + 495,
                                                                                                         740
                                                                                                 )));
        auto listBoxGame = _mapExtra.find<irr::gui::IGUIListBox *>("listGameSaved");

        if (!listBoxGame)
            EXCEPTION(std::runtime_error, "listBoxGame are null");

        for (const auto& obj :  _core.getSaveGame()) {
            res.clear();
            if (obj.find(':') != std::string::npos)
                res.append("Username: " + obj.substr(0, obj.find(':')));
            if (obj.find(';') != std::string::npos) {
                std::string temp(obj.substr(obj.find(':') + 1, std::string::npos));
                res.append(" Level: " + temp.substr(0, temp.find(';')));
            }
            if (obj.find('|') != std::string::npos) {
                std::string temp(obj.substr(obj.find(';') + 1));
                res.append(" Score: " + temp.substr(0, temp.find('|')));
            }
            if (obj.find(':') != std::string::npos) {
                std::string temp(obj.substr(obj.find('|') + 1));
                temp = temp.substr(obj.find(':') + 1);
                res.append(" Speed: " + temp.substr(0, temp.find(';')));
            }
            if (obj.find(':') != std::string::npos) {
                std::string temp(obj.substr(obj.find('|') + 1));
                temp = temp.substr(obj.find(';') + 1);
                temp = temp.substr(temp.find(':') + 1);
                res.append(" Range: " + temp.substr(0, temp.find(';')));
            }
            if (obj.find(':') != std::string::npos) {
                std::string temp(obj.substr(obj.find('|') + 1));
                temp = temp.substr(obj.find(';') + 1);
                temp = temp.substr(temp.find(';') + 1);
                temp = temp.substr(temp.find(':') + 1);
                res.append(" Bomb: " + temp);
            }

            const irr::core::stringw item(res.c_str());

            listBoxGame->addItem(item.c_str());
            listBoxGame->setItemOverrideColor(index, irr::video::SColor(255, 255, 165, 0));
            listBoxGame->setItemOverrideColor(index, irr::gui::EGUI_LISTBOX_COLOR::EGUI_LBC_TEXT_HIGHLIGHT, irr::video::SColor(255, 255, 255, 255));
            index++;
        }

        listBoxGame->setAutoScrollEnabled(true);
        listBoxGame->setItemHeight(50);
    }

    const MapAnyTypes &LoadGame::getMapExtra() const
    {
        return _mapExtra;
    }

    void LoadGame::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
        if (_mapExtra.size() != 0)
            _mapExtra.clear();
    }

    void LoadGame::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "loadGame") {
            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back texture are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                                 "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover",
                                                                                      "backHover texture are not found");

            auto goButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "go",
                                                                              "go texture are not found");
            auto goTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "go",
                                                                               "go texture are not found");
            auto goHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "goHover",
                                                                                    "goHover texture are not found");

            if (!_hoverBack &&
                backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                backButton->setImage(backHoverTexture);
                _hoverBack = true;
            } else if (_hoverBack && !backButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverBack = false;
                backButton->setImage(backTexture);
            }
            if (!_hoverGo &&
                goButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                goButton->setImage(goHoverTexture);
                _hoverGo = true;
            } else if (_hoverGo &&
                       !goButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                _hoverGo = false;
                goButton->setImage(goTexture);
            }
        }
    }

    std::string LoadGame::getUsername() {
        return ("");
    }
}