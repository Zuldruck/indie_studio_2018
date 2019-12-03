/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include "ControlKey.hpp"
#include "Menu.hpp"

namespace ind {
    ControlKey::ControlKey(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver * driver) : _receiver(core),  _core(core)
    {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _controlKeySceneManager = temp->createNewSceneManager(false);

        if (_controlKeySceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _controlKeySceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* set to default value the attributes */

        _saveDevice = device;
        _saveDriver = driver;

        _active = false;
        _hoverBack = false;

        path = getcwd(nullptr,0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/btn_back.png"), "btn_back can't be found.");
        auto backHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");
        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/logo.png"), "logo can't be found.");

        auto runPlayer1 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-z.png"), "key-z can't be found.");
        auto backPlayer1 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-s.png"), "key-s can't be found.");
        auto leftPlayer1 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-q.png"), "key-q can't be found.");
        auto rightPlayer1 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-d.png"), "key-d can't be found.");

        auto runPlayer2 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-up.png"), "key-up can't be found.");
        auto backPlayer2 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-down.png"), "key-down can't be found.");
        auto leftPlayer2 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-left.png"), "key-left can't be found.");
        auto rightPlayer2 = ind::Menu::getTextureWithExcept(driver, std::string( path + "/Assets/menu/key/key-right.png"), "key-right can't be found.");
        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backHoverTexture));
        _mapTextures.insert(std::make_pair("logo", logoTexture));

        _mapTextures.insert(std::make_pair("runPlayer1", runPlayer1));
        _mapTextures.insert(std::make_pair("backPlayer1", backPlayer1));
        _mapTextures.insert(std::make_pair("leftPlayer1", leftPlayer1));
        _mapTextures.insert(std::make_pair("rightPlayer1", rightPlayer1));
        _mapTextures.insert(std::make_pair("runPlayer2", runPlayer2));
        _mapTextures.insert(std::make_pair("leftPlayer2", leftPlayer2));
        _mapTextures.insert(std::make_pair("rightPlayer2", rightPlayer2));
        _mapTextures.insert(std::make_pair("backPlayer2", backPlayer2));
    }

    void ControlKey::drawGUi(float delta)
    {
        if (_activeMenu != "controlKey" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _controlKeySceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool ControlKey::isActive() const
    {
        return _active;
    }

    void ControlKey::setActive(bool _active)
    {
        ControlKey::_active = _active;
    }

    void ControlKey::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        _saveDevice = device;
        _saveDriver = driver;

        device->setEventReceiver(&_receiver);

        this->createImages(device, driver);
        this->createButtons(device, driver);
        this->createTexts(device, driver);
        this->createExtra(device, driver);
    }

    void ControlKey::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        auto height = 	device->getVideoDriver()->getScreenSize().Height;
        auto width 	= 	device->getVideoDriver()->getScreenSize().Width;

        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "logo", "logo texture are not found");

        auto runPlayer1 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "runPlayer1", "runPlayer1 texture are not found");
        auto backPlayer1 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "backPlayer1", "backPlayer1 texture are not found");
        auto leftPlayer1 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "leftPlayer1", "leftPlayer1 texture are not found");
        auto rightPlayer1 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "rightPlayer1", "rightPlayer1 texture are not found");

        auto runPlayer2 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "runPlayer2", "runPlayer2 texture are not found");
        auto backPlayer2 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "backPlayer2", "backPlayer2 texture are not found");
        auto leftPlayer2 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "leftPlayer2", "leftPlayer2 texture are not found");
        auto rightPlayer2 = ind::Menu::findWithExcept<irr::video::ITexture*>(_mapTextures, "rightPlayer2", "rightPlayer2 texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10,10))));

        _mapImages.insert(std::make_pair("runPlayer1", _guiScene->addImage(runPlayer1, irr::core::position2d<int>(width / 2 + 60 - 150 - 300,height / 2 - 65))));
        _mapImages.insert(std::make_pair("backPlayer1", _guiScene->addImage(backPlayer1, irr::core::position2d<int>(width / 2 + 60 - 150 - 300,height / 2 + 100))));
        _mapImages.insert(std::make_pair("leftPlayer1", _guiScene->addImage(leftPlayer1, irr::core::position2d<int>(width / 2 + 60 - 150 - 500,height / 2 + 100))));
        _mapImages.insert(std::make_pair("rightPlayer1", _guiScene->addImage(rightPlayer1, irr::core::position2d<int>(width / 2 + 60 - 150 - 100,height / 2 + 100))));

        _mapImages.insert(std::make_pair("runPlayer2", _guiScene->addImage(runPlayer2, irr::core::position2d<int>(width / 2 + 60 - 150 + 300 + 162 / 2,height / 2 - 65))));
        _mapImages.insert(std::make_pair("backPlayer2", _guiScene->addImage(backPlayer2, irr::core::position2d<int>(width / 2 + 60 - 150 + 300 + 162 / 2,height / 2 + 100))));
        _mapImages.insert(std::make_pair("rightPlayer2", _guiScene->addImage(rightPlayer2, irr::core::position2d<int>(width / 2 + 60 - 150 + 500 + 162 / 2,height / 2 + 100))));
        _mapImages.insert(std::make_pair("leftPlayer2", _guiScene->addImage(leftPlayer2, irr::core::position2d<int>(width / 2 + 60 - 150 + 100 + 162 / 2,height / 2 + 100))));
    }

    void ControlKey::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        auto height = 	device->getVideoDriver()->getScreenSize().Height;
        auto width 	= 	device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(irr::core::rect<ind_int>(width / 2 - 192 + 50,height / 2 + 400,width / 2 + 192 + 50,height / 2 + 400 + 93), 0, GUI_ID_RUN_PRINCIPAL,
                                                                       L"", L"Return to the main menu")));
        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back", "back button are not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back", "back texture are not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
    }

    void ControlKey::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
        auto height = 	device->getVideoDriver()->getScreenSize().Height;
        auto width = 	device->getVideoDriver()->getScreenSize().Width;

        _mapTexts.insert(std::make_pair("player1",
                                        _guiScene->addStaticText(L"PLAYER 1", irr::core::rect<ind_int>(width / 2 + 60 - 150 - 310,height / 2 - 170,width / 2 + 60 - 150 + 310, height / 2 + 170), false)));

        _mapTexts.insert(std::make_pair("player2",
                                        _guiScene->addStaticText(L"PLAYER 2", irr::core::rect<ind_int>(width / 2 + 60 - 150 + 350,height / 2 - 170,width / 2 + 60 - 150 + 650, height / 2 + 170), false)));

        auto textP1 = _mapTexts.find("player1");
        auto textP2 = _mapTexts.find("player2");

        textP1->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textP1->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

        textP2->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
        textP2->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    }

    void ControlKey::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver)
    {
    }

    void ControlKey::cleanScope()
    {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
        if (!_mapKey.empty())
            _mapTexts.clear();
    }

    void ControlKey::updateGUI(float delta)
    {
        if (_saveDevice && _activeMenu == "controlKey") {
            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back", "back texture are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back", "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover", "backHover texture are not found");

            /* play with these Assets */
            if (!_hoverBack && backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                backButton->setImage(backHoverTexture);
                _hoverBack = true;
            } else if (_hoverBack && !backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                _hoverBack = false;
                backButton->setImage(backTexture);
            }
        }
    }

    ControlKey::~ControlKey()
    {}

    std::string ControlKey::getUsername() {
        return ("");
    }
}

