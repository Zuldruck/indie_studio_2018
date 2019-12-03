/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "Principal.hpp"

namespace ind {
    Principal::Principal(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) : _core(core)/*: _receiver(device)*/
    {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        _hoverMulti = false;
        _hoverCredits = false;
        _hoverSettings = false;
        _hoverSolo = false;
        _hoverExit = false;

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "get_firstSceneManger failed");

        _firstSceneManger = temp->createNewSceneManager(false);

        if (_firstSceneManger == nullptr)
            EXCEPTION(std::runtime_error, "createNew_firstSceneManger failed");
            
        _guiScene = _firstSceneManger->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        _receiver = new EventReceiverMenu(core);

        if (_receiver == nullptr)
            EXCEPTION(std::runtime_error, "new EventReceiver failed");

        /* set to default value the attributes */
        _active = true;
        _saveDevice = device;
        _saveDriver = driver;


        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        _hoverMulti = false;
        _hoverCredits = false;
        _hoverSettings = false;
        _hoverSolo = false;

        /* load textures */
        auto multiTexture = ind::Menu::getTextureWithExcept(driver,
                                                            std::string(path + "/Assets/menu/btn_multiplayer.png"),
                                                            "btn_multiplayer can't be found.");
        auto multiHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_multiplayers_hoover.png"), "btn_multiplayers_hoover can't be found.");

        auto soloTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_solo.png"),
                                                           "btn_solo can't be found.");
        auto soloHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_solo_hoover.png"), "btn_solo_hoover can't be found.");

        auto creditsTexture = ind::Menu::getTextureWithExcept(driver,
                                                              std::string(path + "/Assets/menu/btn_credits.png"),
                                                              "btn_credits can't be found.");
        auto creditsHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_credits_hoover.png"), "btn_credits_hoover can't be found.");

        auto settingsTexture = ind::Menu::getTextureWithExcept(driver,
                                                               std::string(path + "/Assets/menu/btn_settings.png"),
                                                               "btn_settings can't be found.");
        auto settingsHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_settings_hoover.png"), "btn_settings_hoover can't be found.");

        auto exitTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_exit.png"),
                                                           "btn_exit can't be found.");
        auto exitHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_exit_hoover.png"), "btn_exit_hoover can't be found.");


        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/logo.png"),
                                                           "logo can't be found.");


        /* add textures */
        _mapTextures.insert(std::make_pair("multiPlayer", multiTexture));
        _mapTextures.insert(std::make_pair("multiPlayerHover", multiHoverTexture));

        _mapTextures.insert(std::make_pair("soloPlayer", soloTexture));
        _mapTextures.insert(std::make_pair("soloPlayerHover", soloHoverTexture));

        _mapTextures.insert(std::make_pair("credits", creditsTexture));
        _mapTextures.insert(std::make_pair("creditsHover", creditsHoverTexture));

        _mapTextures.insert(std::make_pair("settings", settingsTexture));
        _mapTextures.insert(std::make_pair("settingsHover", settingsHoverTexture));

        _mapTextures.insert(std::make_pair("exit", exitTexture));
        _mapTextures.insert(std::make_pair("exitHover", exitHoverTexture));

        _mapTextures.insert(std::make_pair("logo", logoTexture));

        this->createGUI(device, driver);
    }

    Principal::~Principal() {
    }

    void Principal::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void Principal::drawGUi(float delta) {
        if (_activeMenu != "principal" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _firstSceneManger->drawAll();
        _guiScene->drawAll();
    }

    bool Principal::isActive() const {
        return _active;
    }

    void Principal::setActive(bool _active) {
        Principal::_active = _active;
    }

    void Principal::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("SoloButton", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height / 2 - (120), 192 + 192, height / 2 - (120) + 93), 0,
                GUI_ID_RUN_SOLO,
                L"", L"Play a solo player game")));
        _mapButtons.insert(std::make_pair("MultiButton", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height / 2, 192 + 192, height / 2 + 93), 0, GUI_ID_RUN_MULTI,
                L"", L"Play a multi player game")));
        _mapButtons.insert(std::make_pair("SettingsButton", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height / 2 + 120, 192 + 192, height / 2 + 120 + 93), nullptr,
                GUI_ID_RUN_SETTINGS,
                L"", L"Launches a settings Menu")));
        _mapButtons.insert(std::make_pair("CreditsButton", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height / 2 + 240, 192 + 192, height / 2 + 240 + 93), nullptr,
                GUI_ID_RUN_CREDITS,
                L"", L"Launches a credits Menu")));
        _mapButtons.insert(std::make_pair("ExitButton", _guiScene->addButton(
                irr::core::rect<ind_int>(0, height / 2 + 360, 192 + 192, height / 2 + 360 + 93), nullptr,
                GUI_ID_QUIT_BUTTON,
                L"", L"Launches a credits Menu")));
        /* find Buttons */
        auto SoloButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "SoloButton",
                                                                            "solo button are not found");
        auto MultiButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "MultiButton",
                                                                             "multi button are not found");
        auto SettingsButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "SettingsButton",
                                                                                "settings button are not found");
        auto CreditsButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "CreditsButton",
                                                                               "credits button are not found");
        auto ExitButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "ExitButton",
                                                                            "Exit button are not found");

        /* find textures */
        auto soloTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "soloPlayer",
                                                                             "soloPlayer texture are not found");
        auto multiTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "multiPlayer",
                                                                              "multiPlayer texture are not found");
        auto settingsTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "settings",
                                                                                 "settings texture are not found");
        auto creditsTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "credits",
                                                                                "credits texture are not found");
        auto exitTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "exit",
                                                                             "credits texture are not found");

        /* play with these buttons */
        SoloButton->setImage(soloTexture);
        MultiButton->setImage(multiTexture);
        SettingsButton->setImage(settingsTexture);
        CreditsButton->setImage(creditsTexture);
        ExitButton->setImage(exitTexture);
    }

    void Principal::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void Principal::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void Principal::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo",
                                                                             "logo texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10, 10))));
    }

    void Principal::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
    }

    void Principal::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "principal") {

            /* find Buttons */
            auto SoloButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "SoloButton",
                                                                                "solo button are not found");
            auto MultiButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "MultiButton",
                                                                                 "solo button are not found");
            auto SettingsButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "SettingsButton",
                                                                                    "solo button are not found");
            auto CreditsButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "CreditsButton",
                                                                                   "solo button are not found");
            auto ExitButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "ExitButton",
                                                                                "solo button are not found");

            /* find texture and their hover texture too */
            auto soloTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "soloPlayer",
                                                                                 "soloPlayer texture are not found");
            auto soloHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "soloPlayerHover",
                                                                                      "soloPlayerHover texture are not found");
            auto multiTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "multiPlayer",
                                                                                  "multiPlayer texture are not found");
            auto multiHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "multiPlayerHover",
                                                                                       "multiPlayerHover texture are not found");
            auto settingsTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "settings",
                                                                                     "settings texture are not found");
            auto settingsHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "settingsHover",
                                                                                          "settingsHover texture are not found");
            auto creditsTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "credits",
                                                                                    "credits texture are not found");
            auto creditsHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "creditsHover",
                                                                                         "creditsHover texture are not found");
            auto exitTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "exit",
                                                                                 "exit texture are not found");
            auto exithoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "exitHover",
                                                                                      "exitHover texture are not found");

            if (!_hoverMulti &&
                MultiButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                MultiButton->setImage(multiHoverTexture);
                _hoverMulti = true;
            } else if (_hoverMulti && !MultiButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverMulti = false;
                MultiButton->setImage(multiTexture);
            }
            if (!_hoverSettings &&
                SettingsButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                SettingsButton->setImage(settingsHoverTexture);
                _hoverSettings = true;
            } else if (_hoverSettings && !SettingsButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverSettings = false;
                SettingsButton->setImage(settingsTexture);
            }
            if (!_hoverCredits &&
                CreditsButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                CreditsButton->setImage(creditsHoverTexture);
                _hoverCredits = true;
            } else if (_hoverCredits && !CreditsButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverCredits = false;
                CreditsButton->setImage(creditsTexture);
            }
            if (!_hoverSolo &&
                SoloButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                SoloButton->setImage(soloHoverTexture);
                _hoverSolo = true;
            } else if (_hoverSolo && !SoloButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverSolo = false;
                SoloButton->setImage(soloTexture);
            }
            if (!_hoverExit &&
                ExitButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                ExitButton->setImage(exithoverTexture);
                _hoverExit = true;
            } else if (_hoverExit && !ExitButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverExit = false;
                ExitButton->setImage(exitTexture);
            }
        }
    }

    std::string Principal::getUsername() {
        return ("");
    }
}
