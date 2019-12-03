/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include "MultiPlayerMode.hpp"

namespace ind {
    MultiPlayerMode::~MultiPlayerMode() {}

    MultiPlayerMode::MultiPlayerMode(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) : _receiver(core), _core(core)
    {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _MultiPlayerSceneManager = temp->createNewSceneManager(false);

        if (_MultiPlayerSceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _MultiPlayerSceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* set to default value the attributes */
        _saveDevice = device;
        _saveDriver = driver;

        _active = false;
        _hoverBack = false;
        _hoverPlay = false;

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

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backHoverTexture));
        _mapTextures.insert(std::make_pair("logo", logoTexture));
    }

    void MultiPlayerMode::drawGUi(float delta) {
        if (_activeMenu != "multiPlayerMode" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _MultiPlayerSceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool MultiPlayerMode::isActive() const {
        return _active;
    }

    void MultiPlayerMode::setActive(bool _active) {
        MultiPlayerMode::_active = _active;
    }

    void MultiPlayerMode::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {

        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(&_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);

    }

    void MultiPlayerMode::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {

        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo",
                                                                             "logo texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10, 10))));

    }


    void MultiPlayerMode::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {

        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/

        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 250, width / 2 + 192,
                                              height / 2 + 250 + 93), 0, GUI_ID_RUN_MULTI,
                L"", L"Return to the main menu")));

        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                            "back button are not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                             "back texture are not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
    }

    void MultiPlayerMode::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void MultiPlayerMode::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void MultiPlayerMode::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
    }

    void MultiPlayerMode::updateGUI(float delta) {

        if (_saveDevice && _activeMenu == "multiPlayerMode") {

            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back texture are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                                 "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover",
                                                                                      "backHover texture are not found");

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
        }
    }

    std::string MultiPlayerMode::getUsername() {
        return ("");
    }
}