/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "Settings.hpp"

namespace ind {
    Settings::~Settings() {
    }

    Settings::Settings(Core &core, irr::IrrlichtDevice *device, std::shared_ptr<DjControl> _engineSound,
                       irr::video::IVideoDriver *driver) : _receiver(core, _engineSound), _core(core)
    {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _settingsSceneManager = temp->createNewSceneManager(false);

        if (_settingsSceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _settingsSceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* set to default value the attributes */
        _saveEngineSound = std::move(_engineSound);
        _saveDevice = device;
        _saveDriver = driver;

        _active = false;
        _hoverBack = false;
        _hoverControl = false;

        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_back.png"),
                                                           "btn_back can't be found.");
        auto backHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");

        auto controlTexture = ind::Menu::getTextureWithExcept(driver,
                                                              std::string(path + "/Assets/menu/btn_key.png"),
                                                              "btn_key can't be found.");
        auto controlHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_key_hoover.png"), "btn_key_hoover can't be found.");

        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/logo.png"),
                                                           "logo can't be found.");

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backHoverTexture));
        _mapTextures.insert(std::make_pair("control", controlTexture));
        _mapTextures.insert(std::make_pair("controlHover", controlHoverTexture));
        _mapTextures.insert(std::make_pair("logo", logoTexture));
    }

    void Settings::drawGUi(float delta) {
        if (_activeMenu != "settings" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _settingsSceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool Settings::isActive() const {
        return _active;
    }

    void Settings::setActive(bool _active) {
        Settings::_active = _active;
    }

    void Settings::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        _saveDevice = device;
        _saveDriver = driver;

        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        device->setEventReceiver(&_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void Settings::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo",
                                                                             "logo texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10, 10))));
    }

    void Settings::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;


        /* init buttons*/
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 250, width / 2 + 192,
                                         height / 2 + 250 + 93), 0, GUI_ID_RUN_PRINCIPAL,
                L"", L"Return to the main menu")));
        _mapButtons.insert(std::make_pair("control", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 120, width / 2 + 192,
                                         height / 2 + 120 + 93), 0, GUI_ID_RUN_CONTROL_KEY,
                L"", L"Go to the settings key")));
        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                            "back button are not found");
        auto controlButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "control",
                                                                               "control button are not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                             "back texture are not found");
        auto controlTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "control",
                                                                                "control texture are not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
        controlButton->setImage(controlTexture);
    }

    void Settings::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        _mapTexts.insert(std::make_pair("volumeLabel",
                                        _guiScene->addStaticText(L"VOLUME CONTROL:",
                                                                 irr::core::rect<ind_int>(width / 2 - 400,
                                                                                          height / 2 - 80,
                                                                                          width / 2 + 400,
                                                                                          height / 2 - 80 + 100),
                                                                 false)));

        auto textVolume = _mapTexts.find("volumeLabel");

        textVolume->second->setOverrideFont(
                this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textVolume->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    }

    void Settings::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* Init Extra's */
        _mapExtra.insert<irr::gui::IGUIScrollBar *>("scrollbar", _guiScene->addScrollBar(true,
                                                                                         irr::core::rect<ind_int>(
                                                                                                 width / 2 - 400,
                                                                                                 height / 2,
                                                                                                 width / 2 + 400,
                                                                                                 height / 2 + 40),
                                                                                         nullptr,
                                                                                         GUI_ID_VOLUME_SCROLL_BAR));

        /* Custom Extra's */
        auto scrollBar = _mapExtra.find<irr::gui::IGUIScrollBar *>("scrollbar");

        if (!scrollBar)
            EXCEPTION(std::runtime_error, "scrollbar are null");

        scrollBar->setMax(100);
        scrollBar->setPos(_saveEngineSound->getVolumeOfASong("soundMenu"));
    }

    void Settings::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
        if (_mapExtra.size() != 0)
            _mapExtra.clear();
    }

    void Settings::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "settings") {

            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back texture are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                                 "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover",
                                                                                      "backHover texture are not found");

            auto controlButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "control",
                                                                                   "control texture are not found");
            auto controlTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "control",
                                                                                    "control texture are not found");
            auto controlHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "controlHover",
                                                                                         "controlHover texture are not found");

            if (!_hoverBack &&
                controlButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                controlButton->setImage(controlHoverTexture);
                _hoverBack = true;
            } else if (_hoverBack && !controlButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverBack = false;
                controlButton->setImage(controlTexture);
            }
            if (!_hoverControl &&
                backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                backButton->setImage(backHoverTexture);
                _hoverControl = true;
            } else if (_hoverControl && !backButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverControl = false;
                backButton->setImage(backTexture);
            }
        }
    }

    std::string Settings::getUsername() {
        return ("");
    }

}