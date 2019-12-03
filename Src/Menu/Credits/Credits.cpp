/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/
#include "Credits.hpp"

namespace ind {

    Credits::~Credits() = default;

    Credits::Credits(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) : _receiver(core), _core(core)
    {
        /* init new sceneManaer */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _creditsSceneManager = temp->createNewSceneManager(false);

        if (_creditsSceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _creditsSceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* init to default the attributes */
        _saveDevice = device;
        _saveDriver = driver;

        _active = false;
        _hoverBack = false;

        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_back.png"),
                                                           "btn_back can't be found.");
        auto backTextureHover = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");
        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/logo.png"),
                                                           "logo can't be found.");


        auto nicoTexture = ind::Menu::getTextureWithExcept(driver,
                                                           std::string(path + "/Assets/menu/credits/nicolas.png"),
                                                           "nicolas texture can't be found.");
        auto clementTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/credits/clement.png"), "clement texture can't be found.");
        auto leosTexture = ind::Menu::getTextureWithExcept(driver,
                                                           std::string(path + "/Assets/menu/credits/leos.png"),
                                                           "leos texture can't be found.");
        auto lucasTexture = ind::Menu::getTextureWithExcept(driver,
                                                            std::string(path + "/Assets/menu/credits/lucas.png"),
                                                            "lucas texture can't be found.");
        auto robinTexture = ind::Menu::getTextureWithExcept(driver,
                                                            std::string(path + "/Assets/menu/credits/robin.png"),
                                                            "robin texture can't be found.");
        auto simonTexture = ind::Menu::getTextureWithExcept(driver,
                                                            std::string(path + "/Assets/menu/credits/simon.png"),
                                                            "simon texture can't be found.");

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backTextureHover));
        _mapTextures.insert(std::make_pair("logo", logoTexture));

        _mapTextures.insert(std::make_pair("nicoTexture", nicoTexture));
        _mapTextures.insert(std::make_pair("clementTexture", clementTexture));
        _mapTextures.insert(std::make_pair("leosTexture", leosTexture));
        _mapTextures.insert(std::make_pair("lucasTexture", lucasTexture));
        _mapTextures.insert(std::make_pair("robinTexture", robinTexture));
        _mapTextures.insert(std::make_pair("simonTexture", simonTexture));
    }

    void Credits::drawGUi(float delta) {
        if (_activeMenu != "credits" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _creditsSceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool Credits::isActive() const {
        return _active;
    }

    void Credits::setActive(bool _active) {
        Credits::_active = _active;
    }

    void Credits::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(&_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void Credits::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        /* textures find */
        auto nicoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "nicoTexture",
                                                                             "nicoTexture texture are not found");
        auto clementTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "clementTexture",
                                                                                "clementTexture texture are not found");
        auto leosTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "leosTexture",
                                                                             "leosTexture texture are not found");
        auto lucasTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "lucasTexture",
                                                                              "lucasTexture texture are not found");
        auto robinTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "robinTexture",
                                                                              "robinTexture texture are not found");
        auto simonTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "simonTexture",
                                                                              "simonTexture texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("nicoTexture",
                                         _guiScene->addImage(nicoTexture, irr::core::position2d<int>(50 + 360, 50))));
        _mapImages.insert(std::make_pair("clementTexture", _guiScene->addImage(clementTexture,
                                                                               irr::core::position2d<int>(50 + 360,
                                                                                                          70 + 430))));
        _mapImages.insert(std::make_pair("leosTexture",
                                         _guiScene->addImage(leosTexture, irr::core::position2d<int>(450 + 360, 50))));
        _mapImages.insert(std::make_pair("lucasTexture", _guiScene->addImage(lucasTexture,
                                                                             irr::core::position2d<int>(450 + 360,
                                                                                                        70 + 430))));
        _mapImages.insert(std::make_pair("robinTexture",
                                         _guiScene->addImage(robinTexture, irr::core::position2d<int>(850 + 360, 50))));
        _mapImages.insert(std::make_pair("simonTexture", _guiScene->addImage(simonTexture,
                                                                             irr::core::position2d<int>(850 + 360,
                                                                                                        90 + 430))));
    }

    void Credits::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 430, width / 2 + 192,
                                              height / 2 + 430 + 93), 0, GUI_ID_RUN_PRINCIPAL,
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

    void Credits::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {

    }

    void Credits::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {}

    void Credits::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
    }

    void Credits::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "credits") {

            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back button are not found");
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

    std::string Credits::getUsername() {
        return ("");
    }
}