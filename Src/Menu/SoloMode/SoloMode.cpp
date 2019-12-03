/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#include "SoloMode.hpp"
#include "ScoreManager.hpp"
#include <ctime>
#include <boost/algorithm/string.hpp>
#include "GameUI.hpp"

namespace ind {
    SoloMode::~SoloMode()
    = default;

    SoloMode::SoloMode(Core &core, irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) : _receiver(core), _core(core) {
        /* init new sceneManager */
        irr::scene::ISceneManager *temp = device->getSceneManager();

        if (temp == nullptr)
            EXCEPTION(std::runtime_error, "getSceneManager Failed");

        _SoloSceneManager = temp->createNewSceneManager(false);

        if (_SoloSceneManager == nullptr)
            EXCEPTION(std::runtime_error, "createNewSceneManager Failed");

        _guiScene = _SoloSceneManager->getGUIEnvironment();

        if (_guiScene == nullptr)
            EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

        /* set to default value the attributes */
        _active = false;
        path = getcwd(nullptr, 0);
#ifdef __APPLE__
        path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

        _saveDevice = device;
        _saveDriver = driver;

        _hoverPlay = false;
        _hoverLoad = false;
        _hoverBack = false;

        /* load textures */
        auto backTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_back.png"),
                                                           "btn_back can't be found.");
        auto backHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_back_hover.png"), "btn_back_hover can't be found.");

        auto playTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_play.png"),
                                                           "btn_play can't be found.");
        auto playHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_play_hover.png"), "btn_play_hover can't be found.");

        auto loadTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/menu/btn_load.png"),
                                                           "btn_load can't be found.");
        auto loadHoverTexture = ind::Menu::getTextureWithExcept(driver, std::string(
                path + "/Assets/menu/btn_load_hover.png"), "btn_load_hover can't be found.");

        auto logoTexture = ind::Menu::getTextureWithExcept(driver, std::string(path + "/Assets/logo.png"),
                                                           "logo can't be found.");
        auto backgroundEditText = ind::Menu::getTextureWithExcept(driver,
                                                                  std::string(path + "/Assets/menu/edittext.png"),
                                                                  "editText can't be found.");
        auto sign = ind::Menu::getTextureWithExcept(driver,
                                                    std::string(path + "/Assets/menu/sign.png"),
                                                    "sign can't be found.");

        /* add textures */
        _mapTextures.insert(std::make_pair("back", backTexture));
        _mapTextures.insert(std::make_pair("backHover", backHoverTexture));
        _mapTextures.insert(std::make_pair("play", playTexture));
        _mapTextures.insert(std::make_pair("playHover", playHoverTexture));
        _mapTextures.insert(std::make_pair("load", loadTexture));
        _mapTextures.insert(std::make_pair("loadHover", loadHoverTexture));
        _mapTextures.insert(std::make_pair("logo", logoTexture));
        _mapTextures.insert(std::make_pair("editText", backgroundEditText));
        _mapTextures.insert(std::make_pair("sign", sign));
    }

    void SoloMode::drawGUi(float delta) {
        if (_activeMenu != "soloMode" && isActive())
            setActive(false);
        this->updateGUI(delta);
        _SoloSceneManager->drawAll();
        _guiScene->drawAll();
    }

    bool SoloMode::isActive() const {
        return _active;
    }

    void SoloMode::setActive(bool _active) {
        SoloMode::_active = _active;
    }

    void SoloMode::createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
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

    void SoloMode::createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* textures find */
        auto logoTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "logo",
                                                                             "logo texture are not found");
        auto backgroundEditText = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "editText",
                                                                                    "editText texture are not found");
        auto backgroundSignScores = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "sign",
                                                                                      "sign texture are not found");

        /* Init images */
        _mapImages.insert(std::make_pair("logo", _guiScene->addImage(logoTexture, irr::core::position2d<int>(10, 10))));
        _mapImages.insert(std::make_pair("editTextbackground", _guiScene->addImage(backgroundEditText,
                                                                                   irr::core::position2d<int>(
                                                                                           width / 2 - 350,
                                                                                           height / 2 - 60))));

        _mapImages.insert(std::make_pair("sign", _guiScene->addImage(backgroundSignScores,
                                                                     irr::core::position2d<int>(
                                                                             width - backgroundSignScores->getSize().Width,
                                                                             10))));
    }


    void SoloMode::createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;

        /* init buttons*/
        _mapButtons.insert(std::make_pair("back", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 250, width / 2 + 192,
                                         height / 2 + 250 + 93), 0, GUI_ID_RUN_PRINCIPAL,
                L"", L"Return to the main menu")));

        _mapButtons.insert(std::make_pair("play", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 50, width / 2 + 192, height / 2 + 50 + 93),
                0, GUI_ID_RUN_PLAY,
                L"", L"Run solo game")));

        _mapButtons.insert(std::make_pair("load", _guiScene->addButton(
                irr::core::rect<ind_int>(width / 2 - 192, height / 2 + 150, width / 2 + 192,
                                         height / 2 + 150 + 93), 0, GUI_ID_RUN_LOAD,
                L"", L"Load a game")));


        /* find Buttons */
        auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                            "back button are not found");
        auto playButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "play",
                                                                            "play button are not found");
        auto loadButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "load",
                                                                            "load button are not found");

        /* find textures */
        auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                             "back texture are not found");
        auto playTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "play",
                                                                             "play texture are not found");
        auto loadTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "load",
                                                                             "load texture are not found");

        /* play with these buttons */
        backButton->setImage(backTexture);
        playButton->setImage(playTexture);
        loadButton->setImage(loadTexture);
    }


    void SoloMode::createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        /* variables */
        irr::gui::IGUIFont *fontText = nullptr;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *>::iterator objText;

        ind::ScoreManager scores;
        std::vector<ind::ScorePlayer> outputScores;

        std::wstring wide_string;
        std::string narrow_string;
        std::string dateTime;
        const wchar_t *text = nullptr;

        size_t pos = 0;
        int index = 0;
        unsigned int width = 0;


        if (!device || !driver)
            EXCEPTION(std::runtime_error, "device/driver was null");
        width = device->getVideoDriver()->getScreenSize().Width;

        /* createScore */
        scores = ind::ScoreManager();
        scores.setDevice(device);
        scores.loadFromFile();

        /* get scores */
        scores.getScorePlayer();
        outputScores = scores.getScorePlayer();

        /* check if gui scene exists*/
        if (!_guiScene)
            EXCEPTION(std::runtime_error, "_guiScene was null");

        /*get font*/
        fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/SplatchScores.png").c_str());

        /*check font*/
        if (!fontText)
            EXCEPTION(std::runtime_error, "fontText was null");

        auto bgSign = ind::Menu::findWithExcept<irr::gui::IGUIImage*>(_mapImages, "sign", "error when we tried to get the background sign");

        /* loop to create all texts */
        for (const auto &obj : outputScores) {

            if (index >= 3)
                break;

            /*get date*/
            dateTime = ctime(&obj._time);
            std::transform(dateTime.begin(), dateTime.end(), dateTime.begin(), ::toupper);
            pos = dateTime.find(' ');
            if (pos == std::string::npos)
                EXCEPTION(std::runtime_error, "ERROR DATE");
            pos = dateTime.find(' ', pos + 1);
            if (pos == std::string::npos)
                EXCEPTION(std::runtime_error, "ERROR DATE");
            pos = dateTime.find(' ', pos + 1);
            if (pos == std::string::npos)
                EXCEPTION(std::runtime_error, "ERROR DATE");

            /*create Text*/
                narrow_string = (capString(obj._name, 11)  + capString(dateTime.substr(0, pos), 16) + " " + std::to_string(obj._score));
            wide_string = std::wstring(narrow_string.begin(), narrow_string.end());
            text = wide_string.c_str();

            /*add Text*/
            _mapTexts.insert(std::make_pair(std::string("player" + std::to_string(index)),
                                            _guiScene->addStaticText(text, irr::core::rect<ind_int>(width - bgSign->getRelativePosition().getWidth() + 130,
                                                                                                    250 + index * 72,
                                                                                                    width - bgSign->getRelativePosition().getWidth() + 500,
                                                                                                    400 + index * 72),
                                                                     false)));


            /*custom text*/
            objText = _mapTexts.find("player" + std::to_string(index));
            objText->second->setOverrideFont(fontText);
            objText->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

            index++;
        }
    }

    void SoloMode::createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) {
        auto height = device->getVideoDriver()->getScreenSize().Height;
        auto width = device->getVideoDriver()->getScreenSize().Width;
        static_cast<void>(driver);

        /* Init Extra's */
        _mapExtra.insert<irr::gui::IGUIEditBox *>("usernameEntry", _guiScene->addEditBox(L"ENTER YOUR USERNAME",
                                                                                         irr::core::rect<ind_int>(
                                                                                                 width / 2 - 300,
                                                                                                 height / 2 - 50,
                                                                                                 width / 2 + 300,
                                                                                                 height / 2 - 50 +
                                                                                                 80)));

        /* Custom Extra's */
        auto usernameEntry = _mapExtra.find<irr::gui::IGUIEditBox *>("usernameEntry");

        if (!usernameEntry)
            EXCEPTION(std::runtime_error, "usernameEntry was not found.");

        usernameEntry->setMax(19);
        usernameEntry->setDrawBackground(false);
        usernameEntry->setDrawBorder(false);
        usernameEntry->setAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER,
                                    irr::gui::EGUIA_CENTER);
        usernameEntry->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

        irr::gui::IGUIFont *fnt = this->_guiScene->getFont(
                std::string(path + "/Assets/fonts/Splatch.png").c_str());

        if (!fnt)
            EXCEPTION(std::runtime_error, "fnt Splatch was null.");
        usernameEntry->setOverrideFont(fnt);
    }

    void SoloMode::cleanScope() {
        if (!_mapButtons.empty())
            _mapButtons.clear();
        if (!_mapImages.empty())
            _mapImages.clear();
        if (!_mapTexts.empty())
            _mapTexts.clear();
        if (_mapExtra.size() != 0)
            _mapExtra.clear();
    }

    void SoloMode::updateGUI(float delta) {
        if (_saveDevice && _activeMenu == "soloMode") {

            /* find Assets */
            auto backButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "back",
                                                                                "back texture are not found");
            auto backTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "back",
                                                                                 "back texture are not found");
            auto backHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "backHover",
                                                                                      "backHover texture are not found");

            auto loadButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "load",
                                                                                "load texture are not found");
            auto loadTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "load",
                                                                                 "load texture are not found");
            auto loadHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "loadHover",
                                                                                      "loadHover texture are not found");

            auto playButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "play",
                                                                                "play texture are not found");
            auto playTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "play",
                                                                                 "play texture are not found");
            auto playHoverTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "playHover",
                                                                                      "playHover texture are not found");

            if (!_hoverBack &&
                backButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                backButton->setImage(backHoverTexture);
                _hoverBack = true;
            } else if (_hoverBack && !backButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverBack = false;
                backButton->setImage(backTexture);
            }
            if (!_hoverLoad &&
                loadButton->getRelativePosition().isPointInside(_saveDevice->getCursorControl()->getPosition())) {
                loadButton->setImage(loadHoverTexture);
                _hoverLoad = true;
            } else if (_hoverLoad && !loadButton->getRelativePosition().isPointInside(
                    _saveDevice->getCursorControl()->getPosition())) {
                _hoverLoad = false;
                loadButton->setImage(loadTexture);
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

            ind::ScoreManager scores;
            std::vector<ind::ScorePlayer> outputScores;

            std::wstring wide_string;
            std::string narrow_string;
            std::string dateTime;
            const wchar_t *text = nullptr;

            size_t pos = 0;
            int index = 0;

            /* createScore */
            scores = ind::ScoreManager();
            scores.setDevice(_saveDevice);
            scores.loadFromFile();

            /* get scores */
            scores.getScorePlayer();
            outputScores = scores.getScorePlayer();

            /* loop to update all texts */
            for (const auto &obj : outputScores) {

                if (index >= 3)
                    break;

                /*get date*/
                dateTime = ctime(&obj._time);
                std::transform(dateTime.begin(), dateTime.end(), dateTime.begin(), ::toupper);
                pos = dateTime.find(' ');
                if (pos == std::string::npos)
                    EXCEPTION(std::runtime_error, "ERROR DATE");
                pos = dateTime.find(' ', pos + 1);
                if (pos == std::string::npos)
                    EXCEPTION(std::runtime_error, "ERROR DATE");
                pos = dateTime.find(' ', pos + 1);
                if (pos == std::string::npos)
                    EXCEPTION(std::runtime_error, "ERROR DATE");

                /*create Text*/
                narrow_string = (capString(obj._name, 11) +  "° "  + capString(dateTime.substr(0, pos), 14) + std::to_string(obj._score));
                wide_string = std::wstring(narrow_string.begin(), narrow_string.end());
                text = wide_string.c_str();

                /*add Text*/
                auto objText = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "player" + std::to_string(index), "error when we tried to get the player n index");

                /*custom text*/
                objText->setText(text);
                index++;
            }
        }
    }

    std::string SoloMode::getUsername() {
        /* Custom Extra's */
        auto usernameEntry = _mapExtra.find<irr::gui::IGUIEditBox *>("usernameEntry");

        if (!usernameEntry)
            EXCEPTION(std::runtime_error, "usernameEntry was not found.");

        std::wstring ws(usernameEntry->getText());
        std::string res(ws.begin(), ws.end());

        return (res);
    }

    std::string SoloMode::capString(std::string value, unsigned int numberMax)
    {
        if (value.size() + 1 == numberMax)
            return value;
        if (value.size() + 1 > numberMax) {
            return value.substr(0, numberMax);
        } else {
            for (unsigned i = value.size() ; i < numberMax ; i++)
                value += "° ";
            return value;
        }
    }

    void SoloMode::setUsername(const std::string& newValue)
    {
         /* Custom Extra's */
        auto usernameEntry = _mapExtra.find<irr::gui::IGUIEditBox *>("usernameEntry");

        if (!usernameEntry)
            EXCEPTION(std::runtime_error, "usernameEntry was not found.");

        usernameEntry->setText(ind::GameUI::convertStringToWchar(newValue).data());
    }
}