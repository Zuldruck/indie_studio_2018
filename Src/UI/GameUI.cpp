/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#include "GameUI.hpp"
#include <ctime>
#include "BomberMan.hpp"
#include "Map.hpp"
#include "Timer.hpp"
#include "Bomber.hpp"

ind::GameUI::GameUI(GameScene *gameScene)
{
    if (!gameScene)
        EXCEPTION(std::runtime_error, "gameScene Was null");

    _gameScene = gameScene;
    _saveDevice = gameScene->getCore().getDevice();
    _saveDriver = gameScene->getCore().getDriver();
    _nbPlayers = _gameScene->getNbPlayer();
    _guiScene = _saveDevice->getSceneManager()->getGUIEnvironment();

    if (_guiScene == nullptr)
        EXCEPTION(std::runtime_error, "getGUIEnvironment failed");

    path = getcwd(nullptr,0);
#ifdef __APPLE__
    path += "/OOP_indie_studio_2018";
#endif /* !__APPLE__ */

    /* TIMER INITIALIZATION */
    _timer = std::make_shared<Timer>();

    this->initTextures();
    this->initPositionsGUI();
    this->initButtons();
    this->initTexts();
    this->initScrollVolume();
}

void ind::GameUI::createStyleUI(unsigned int position)
{
    this->createHUD(position);
    this->createUsername(position);
    this->createPowerUPUI(position);
}

void ind::GameUI::createPowerUPUI(unsigned int position)
{
    this->createBombeNumber(position);
    this->createBombRange(position);
    this->createSpeed(position);
    this->createLevel(1);
}

bool ind::GameUI::update()
{
    if (this->_nbPlayers == 1) {
        return this->timerIsFinished() || this->updateTexts();
    } else {
        return this->updateTexts();
    }
}

bool ind::GameUI::updateTexts()
{
    /* Variables */
    irr::gui::IGUIStaticText *bombRemains = nullptr;
    irr::gui::IGUIStaticText *bombRange = nullptr;
    irr::gui::IGUIStaticText *speed = nullptr;
    irr::gui::IGUIStaticText *level = nullptr;
    irr::gui::IGUIStaticText *score = nullptr;
    auto map = this->_gameScene->getObjectsByTags("MAP")[0];
    auto nbPlayer = this->_gameScene->getNbPlayer();    
    auto mapPlayers = this->_gameScene->getObjectsByTags(nbPlayer == 1 ? "PLAYER" : "CHARACTER");
    int index = 1;

    if (this->_nbPlayers == 1) {
        auto timer = _mapTexts.find("timer");

        /* check iterator */
        if (timer == _mapTexts.end() || !timer->second)
            EXCEPTION(std::runtime_error, "timer was not found");

        /* update timer */
        timer->second->setText(convertStringToWchar(std::to_string(_timer->getSecondsRemains() / 60) + ":" + std::to_string(_timer->getSecondsRemains() % 60)).data());
    }
    /* update all power ups */
    for (const auto& obj : mapPlayers) {
        bombRemains = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, std::string("bomb") + std::to_string(index),"Error when get bomb" + std::to_string(index) + "in the map of texts");
        bombRange = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, std::string("range") + std::to_string(index), "Error when get range bomb" + std::to_string(index) + "in the map of texts");
        speed = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, std::string("speed") + std::to_string(index), "Error when get speed" + std::to_string(index) + "in the map of texts");
        if (this->_nbPlayers == 1) {
            score = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, std::string("scorePlayer"), "Error when get score in the map of texts");
            level = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "level", "Error when level in the map of texts");
            level->setText(convertStringToWchar(std::string("LEVEL " + std::static_pointer_cast<Map>(map)->getName())).data());
            score->setText(convertStringToWchar(std::to_string(_gameScene->getScorePlayer())).data());
        }
        if (std::dynamic_pointer_cast<Bomber>(obj)) {
            bombRemains->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(std::dynamic_pointer_cast<Bomber>(obj))->getBomb())).data());
            bombRange->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(std::dynamic_pointer_cast<Bomber>(obj))->getRange())).data());
            speed->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(std::dynamic_pointer_cast<Bomber>(obj))->getBonusSpeed())).data());
        } else {
            bombRemains->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(obj)->getBomb())).data());
            bombRange->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(obj)->getRange())).data());
            speed->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(obj)->getBonusSpeed())).data());
        }
        index++;
    }
    return (false);
}

void ind::GameUI::pauseAndGameOverUI(void)
{
    auto height = _saveDevice->getVideoDriver()->getScreenSize().Height;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;
    auto homeButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonHome",
                                                                        "buttonHome was not found");

    auto bgPause = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "bgPause",
                                                                     "bgPause button not found");
    auto signPause = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "bgButtonPause",
                                                                       "bgButtonPause button not found");
    auto buttonHome = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonHome",
                                                                        "buttonHome button not found");
    auto buttonExit = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonExit",
                                                                        "buttonExit button not found");
    auto textVolume = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "volumeLabel",
                                                                            "volumeLabel text not found");
    auto pauseGameOverText = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "pause/gameOver",
                                                                                   "pause gameover text not found");

    auto scorePlayerInGame = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "scorePlayer",
                                                                                   "scorePlayer text not found");
    auto scorePlayerTextEndGame = ind::Menu::findWithExcept<irr::gui::IGUIStaticText *>(_mapTexts, "scorePlayerEndGame",
                                                                                        "scorePlayerEndGame text not found");
    auto map = this->_gameScene->getObjectsByTags("MAP")[0];
    auto players = this->_gameScene->getObjectsByTags("CHARACTER");
    std::string winnerUsername;
    unsigned index = 1;

    signPause->setUseAlphaChannel(true);

    auto scrollBar = _mapExtra.find<irr::gui::IGUIScrollBar *>("scrollbar");
    if (!scrollBar)
        EXCEPTION(std::runtime_error, "scrollbar was null");

    if (_paused) {
        if (this->_nbPlayers == 1) {
            auto begin = _timer->getBeginTime();
            auto end = _timer->getTimeEnd();
            auto diff = (_timer->getActualTime() - _lastSecond) / 2;

            _timer->setBeginTime(begin + diff);
            _timer->setTimeEnd(end + diff);
        }

        _paused = false;

        bgPause->setVisible(false);
        signPause->setVisible(false);
        buttonHome->setVisible(false);
        buttonExit->setVisible(false);
        scrollBar->setVisible(false);
        textVolume->setVisible(false);
        pauseGameOverText->setVisible(false);
        scorePlayerTextEndGame->setVisible(false);
    } else {
        if (this->_nbPlayers == 1)
            _lastSecond = _timer->getActualTime();
        _paused = true;
        bgPause->setVisible(true);
        signPause->setVisible(true);
        buttonHome->setVisible(true);
        buttonExit->setVisible(true);
        if (this->_gameScene->isIsGameOver()) {
            if (_gameScene->getCore().getCurrentLevel() == 21) {
                pauseGameOverText->setRelativePosition(irr::core::rect<ind_int>(width / 2 - 400,
                                                                                height / 2 - homeButton->getRelativePosition().getHeight() + 100,
                                                                                width / 2 + 600,
                                                                                height / 2 -homeButton->getRelativePosition().getHeight() + 200));
                pauseGameOverText->setText(L"SOLO MODE FINISHED, CONGRATS !");
                pauseGameOverText->setOverrideColor(irr::video::SColor(255, 63, 195, 128));
            } else
                pauseGameOverText->setText(L"GAME OVER");

            if (_gameScene->getNbPlayer() > 1) {
                for (auto const &obj : players) {
                    if (std::static_pointer_cast<Character>(obj)->isAlive())
                        winnerUsername = std::static_pointer_cast<Character>(obj)->getUsername();
                    index++;
                }
                if (!winnerUsername.empty()) {
                    scorePlayerTextEndGame->setRelativePosition(irr::core::rect<ind_int>(width / 2 - 250,
                                                                                         height / 2 + homeButton->getRelativePosition().getHeight() - 100,
                                                                                         width / 2 + 250,
                                                                                         height / 2 +  homeButton->getRelativePosition().getHeight() - 100 + 100));
                    scorePlayerTextEndGame->setText(convertStringToWchar(std::string("Winner Is: " +  winnerUsername)).data());
                    pauseGameOverText->setOverrideColor(irr::video::SColor(255, 63, 195, 128));
                    scorePlayerTextEndGame->setOverrideColor(irr::video::SColor(255, 63, 195, 128));
                } else {
                    scorePlayerTextEndGame->setRelativePosition(irr::core::rect<ind_int>(width / 2 - 180,
                                                                                         height / 2 + homeButton->getRelativePosition().getHeight() - 100,
                                                                                         width / 2 + 180,
                                                                                         height / 2 +  homeButton->getRelativePosition().getHeight() - 100 + 100));
                    scorePlayerTextEndGame->setText(convertStringToWchar(std::string("NOBODY WIN")).data());
                    pauseGameOverText->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
                    scorePlayerTextEndGame->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
                }
            } else {
                scorePlayerTextEndGame->setText(
                        convertStringToWchar("SCORE: " + std::to_string(_gameScene->getScorePlayer())).data());
                if (_gameScene->getCore().getCurrentLevel()  != 21) {
                    pauseGameOverText->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
                    scorePlayerTextEndGame->setOverrideColor(irr::video::SColor(255, 255, 0, 0));
                }
            }
            scorePlayerTextEndGame->setVisible(true);
            scorePlayerInGame->setVisible(false);
        } else {
            textVolume->setVisible(true);
            pauseGameOverText->setText(L"PAUSE");
            scrollBar->setVisible(true);
        }
        pauseGameOverText->setVisible(true);
    }
}

void ind::GameUI::cleanScope()
{
    if (!_mapButtons.empty())
        _mapButtons.clear();
    if (!_mapImages.empty())
        _mapImages.clear();
    if (!_mapTexts.empty())
        _mapTexts.clear();
    if (_mapExtra.size() != 0)
        _mapExtra.clear();
    if (!_mapTextures.empty())
        _mapTextures.clear();
    if (!_textPosition.empty())
        _mapTextures.clear();
}

bool ind::GameUI::timerIsFinished()
{
    return (_timer->isFinished());
}

void ind::GameUI::createTimer(unsigned int endTime)
{
    /* Variables */
    irr::gui::IGUIFont *fontText = nullptr;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;

    /* check and run timer */
    if (!_timer)
        EXCEPTION(std::runtime_error, "_timer was null");
    _timer->startTimer(_saveDevice, endTime);

    /* create and insert the background of timer */
    auto bgTimerTexture = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgTimer", "bgTimer texture are not found");

    _mapImages.insert(std::make_pair("bgTimer", _guiScene->addImage(bgTimerTexture, irr::core::position2d<int>(width / 2 - bgTimerTexture->getSize().Width / 2, 5))));

    /* add the text to the map */
    _mapTexts.insert(std::make_pair("timer", _guiScene->addStaticText(L"", irr::core::rect<ind_int>(width / 2 - 70, 20, width / 2 + 100, 115), false)));

    /* set parameters to the text */
    auto timer = _mapTexts.find("timer");

    if (timer == _mapTexts.end() || !timer->second)
        EXCEPTION(std::runtime_error, "timer or his background was not found.");

    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/SplatchKey.png").c_str());

    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    timer->second->setOverrideFont(fontText);
    timer->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
}

void ind::GameUI::createUsername(unsigned int position)
{
    /* VARIABLES */
    irr::gui::IGUIFont *fontText = nullptr;
    unsigned int positionHUD = 0;

    position == 1 ? positionHUD = position : position == 2 ? positionHUD = 3 : position == 3 ? positionHUD = 2 : positionHUD = 4;
    /* insert the text in the map of a text */
    _mapTexts.insert(std::make_pair(std::string("userName"+ std::to_string(position)), _guiScene->addStaticText(L"", textConvertPositionIntoRect("username", positionHUD), false)));

    /* set the parameters to this text */
    auto userName = _mapTexts.find(std::string("userName"+ std::to_string(position)));
    if (userName == _mapTexts.end() || !userName->second)
        EXCEPTION(std::runtime_error, "userName was not found.");

    /*get font*/
    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch32.png").c_str());

    /*check font*/
    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    userName->second->setOverrideFont(fontText);
    userName->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

    userName->second->setText(convertStringToWchar(this->_gameScene->getUsername()).data());
}

void ind::GameUI::createLevel(unsigned int position)
{
    if (this->_nbPlayers == 1) {
        /* Variables */
        irr::gui::IGUIFont *fontText = nullptr;
        auto map = this->_gameScene->getObjectsByTags("MAP")[0];

        /* insert the text into the map of texts */
        _mapTexts.insert(std::make_pair("level", _guiScene->addStaticText(L"", textConvertPositionIntoRect("level", position), false)));

        /* set the parameters of this text */
        auto level = _mapTexts.find("level");
        if (level == _mapTexts.end() || !level->second)
            EXCEPTION(std::runtime_error, "level was not found.");

        /*get font*/
        fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch32.png").c_str());

        /*check font*/
        if (!fontText)
            EXCEPTION(std::runtime_error, "fontText was null");

        level->second->setOverrideFont(fontText);
        level->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

        level->second->setText(convertStringToWchar(std::string("LEVEL " + std::static_pointer_cast<Map>(map)->getName())).data());
    }
}

void ind::GameUI::createSpeed(unsigned int position)
{
    unsigned int positionHUD = 0;
    boost::unordered_map<std::string, irr::gui::IGUIStaticText *>::iterator speed;
    irr::gui::IGUIFont *fontText = nullptr;

    position == 1 ? positionHUD = position : position == 2 ? positionHUD = 3 : position == 3 ? positionHUD = 2 : positionHUD = 4;

    /*get the player object to the his bomb number remains */
    auto nbPlayer = this->_gameScene->getNbPlayer();    
    auto mapPlayers = this->_gameScene->getObjectsByTags(nbPlayer == 1 ? "PLAYER" : "CHARACTER");

    /*get font */
    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch26.png").c_str());

    /*check font */
    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    /*insert a text into the map of texts*/
    _mapTexts.insert(std::make_pair(std::string("speed" + std::to_string(position)), _guiScene->addStaticText(L"", textConvertPositionIntoRect("speed", positionHUD), false)));

    /*get the bomb and set his parameters*/
    speed = _mapTexts.find(std::string("speed") + std::to_string(position));
    if (speed == _mapTexts.end() || !speed->second)
        EXCEPTION(std::runtime_error, std::string("speed" + std::to_string(position) + "was not found."));

    speed->second->setOverrideFont(fontText);
    speed->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));

    speed->second->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(mapPlayers[position - 1])->getBonusSpeed())).data());
}

void ind::GameUI::createBombRange(unsigned int position)
{
    boost::unordered_map<std::string, irr::gui::IGUIStaticText *>::iterator range;
    irr::gui::IGUIFont *fontText = nullptr;

    /*get the player object to the his bomb number remains */
    auto nbPlayer = this->_gameScene->getNbPlayer();    
    auto mapPlayers = this->_gameScene->getObjectsByTags(nbPlayer == 1 ? "PLAYER" : "CHARACTER");

    unsigned int positionHUD = 0;

    position == 1 ? positionHUD = position : position == 2 ? positionHUD = 3 : position == 3 ? positionHUD = 2 : positionHUD = 4;

    /*get font */
    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch26.png").c_str());

    /*check font */
    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    /*insert a text into the map of texts*/
    _mapTexts.insert(std::make_pair(std::string("range" + std::to_string(position)),
                                    _guiScene->addStaticText(L"", textConvertPositionIntoRect("range", positionHUD), false)));

    /*get the bomb and set his parameters*/
    range = _mapTexts.find(std::string("range") + std::to_string(position));
    if (range == _mapTexts.end() || !range->second)
        EXCEPTION(std::runtime_error, std::string("range" + std::to_string(position) + "was not found."));

    range->second->setOverrideFont(fontText);
    range->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    range->second->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(mapPlayers[position - 1])->getRange())).data());
}

void ind::GameUI::createBombeNumber(unsigned int position)
{
    boost::unordered_map<std::string, irr::gui::IGUIStaticText *>::iterator numberBomb;
    irr::gui::IGUIFont *fontText = nullptr;

    /*get the player object to the his bomb number remains */
    auto nbPlayer = this->_gameScene->getNbPlayer();    
    auto mapPlayers = this->_gameScene->getObjectsByTags(nbPlayer == 1 ? "PLAYER" : "CHARACTER");

    unsigned int positionHUD = 0;

    position == 1 ? positionHUD = position : position == 2 ? positionHUD = 3 : position == 3 ? positionHUD = 2 : positionHUD = 4;

    /*get font */
    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch26.png").c_str());

    /*check font */
    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    /*insert a text into the map of texts*/
    _mapTexts.insert(std::make_pair(std::string("bomb" + std::to_string(position)),
                                    _guiScene->addStaticText(L"", textConvertPositionIntoRect("bombNumber", positionHUD), false)));

    /*get the bomb and set his parameters*/
    numberBomb = _mapTexts.find(std::string("bomb") + std::to_string(position));
    if (numberBomb == _mapTexts.end() || !numberBomb->second)
        EXCEPTION(std::runtime_error, std::string("bomb" + std::to_string(position) + "was not found."));

    numberBomb->second->setOverrideFont(fontText);
    numberBomb->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    numberBomb->second->setText(convertStringToWchar(std::to_string(std::static_pointer_cast<BomberMan>(mapPlayers[position - 1])->getBomb())).data());
}

void ind::GameUI::createHUD(unsigned int position)
{
    /* create and insert the UI of the first player */
    auto bgHUD = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgHUD",
                                                                   "bgHUD texture are not found");
    auto bgHUDRight = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgHUDRight",
                                                                        "bgHUD texture are not found");

    unsigned int positionHUD = 0;
    position == 1 ? positionHUD = position : position == 2 ? positionHUD = 3 : position == 3 ? positionHUD = 2 : positionHUD = 4;

    if (positionHUD >= 3)
        _mapImages.insert(std::make_pair(std::string("hud" + std::to_string(position)), _guiScene->addImage(bgHUDRight, hudConvertPositionInto2DPos("hud", positionHUD))));
    else
        _mapImages.insert(std::make_pair(std::string("hud" + std::to_string(position)), _guiScene->addImage(bgHUD, hudConvertPositionInto2DPos("hud", positionHUD))));
}

void ind::GameUI::createScore()
{
    boost::unordered_map<std::string, irr::gui::IGUIStaticText *>::iterator score;
    irr::gui::IGUIFont *fontText = nullptr;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;

    /*get the player object to the his bomb number remains */
    auto nbPlayer = this->_gameScene->getNbPlayer();    
    auto mapPlayers = this->_gameScene->getObjectsByTags(nbPlayer == 1 ? "PLAYER" : "CHARACTER");

    /*get font */
    fontText = this->_guiScene->getFont(std::string(path + "/Assets/fonts/SplatchKey.png").c_str());

    /*check font */
    if (!fontText)
        EXCEPTION(std::runtime_error, "fontText was null");

    /*insert a text into the map of texts*/
    _mapTexts.insert(std::make_pair("scorePlayer", _guiScene->addStaticText(L"", irr::core::rect<ind_int>(width - 120 - 70, 20, width - 120 + 100, 115), false)));

    /*get the bomb and set his parameters*/
    score = _mapTexts.find("scorePlayer");
    if (score == _mapTexts.end() || !score->second)
        EXCEPTION(std::runtime_error, std::string("scorePlayer was not found."));

    score->second->setOverrideFont(fontText);
    score->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    score->second->setText(convertStringToWchar(std::to_string(this->_gameScene->getScorePlayer())).data());
    if (_nbPlayers > 1)
        score->second->setVisible(false);
}

std::wstring ind::GameUI::convertStringToWchar(std::string value)
{
    std::wstring wide_string;

    wide_string = std::wstring(value.begin(), value.end());
    return wide_string;
}

irr::core::rect<ind::ind_int> ind::GameUI::textConvertPositionIntoRect(const std::string& key, unsigned int position)
{
    return ind::Menu::findWithExcept<irr::core::rect<ind::ind_int>>(_textPosition, key + std::to_string(position), "error with position 1 get text. Key:" + key + std::to_string(position));
}

irr::core::vector2d<int> ind::GameUI::hudConvertPositionInto2DPos(const std::string &key, unsigned int position)
{
    irr::core::vector2d<int> respos;

    respos = ind::Menu::findWithExcept<irr::core::vector2d<int>>(_hudPosition, key + std::to_string(position),
            "error with position n get hud. Key:" + key +
            std::to_string(position));
    return respos;
}

void ind::GameUI::initTextures()
{
    auto bgTimer = ind::Menu::getTextureWithExcept(_saveDriver,
                                                   std::string(path + "/Assets/UI/bg-timer.png"),
                                                   "bgTimer texture can't be found.");
    auto bgHUD = ind::Menu::getTextureWithExcept(_saveDriver,
                                                 std::string(path + "/Assets/UI/ic-hud-player.png"),
                                                 "bgHUD texture can't be found.");
    auto bgHUDRight = ind::Menu::getTextureWithExcept(_saveDriver,
                                                      std::string(path + "/Assets/UI/ic-hud-player-right.png"),
                                                      "bgHUDRight texture can't be found.");
    auto bgPause = ind::Menu::getTextureWithExcept(_saveDriver,
                                                   std::string(path + "/Assets/UI/bgPause.png"),
                                                   "bgPause texture can't be found.");
    auto bgButtonPause = ind::Menu::getTextureWithExcept(_saveDriver,
                                                         std::string(path + "/Assets/UI/bgButtonPause.png"),
                                                         "bgButtonPause texture can't be found.");
    auto bgButtonHome = ind::Menu::getTextureWithExcept(_saveDriver,
                                                        std::string(path + "/Assets/menu/home.png"),
                                                        "home texture can't be found.");
    auto bgButtonExit = ind::Menu::getTextureWithExcept(_saveDriver,
                                                        std::string(path + "/Assets/menu/exit.png"),
                                                        "exit texture can't be found.");
    /* add textures */
    _mapTextures.insert(std::make_pair("bgTimer", bgTimer));
    _mapTextures.insert(std::make_pair("bgHUD", bgHUD));
    _mapTextures.insert(std::make_pair("bgHUDRight", bgHUDRight));
    _mapTextures.insert(std::make_pair("bgPause", bgPause));
    _mapTextures.insert(std::make_pair("bgButtonPause", bgButtonPause));
    _mapTextures.insert(std::make_pair("bgButtonHome", bgButtonHome));
    _mapTextures.insert(std::make_pair("bgButtonExit", bgButtonExit));
}

void ind::GameUI::initPositionsGUI()
{
    auto height = _saveDevice->getVideoDriver()->getScreenSize().Height;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;
    auto bgHUD = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgHUD",
                                                                   "bgHUD button not found");

    /* POSITION GAME UI INTIALIZATION */
    _textPosition.insert(std::make_pair("username1", irr::core::rect<ind_int>(180, height - 30 - 20, width + 400, height - 30 + 20)));
    _textPosition.insert(std::make_pair("level1", irr::core::rect<ind_int>(180 * 2, height - 70 - 20, width + 400, height - 70 + 20)));
    _textPosition.insert(std::make_pair("speed1", irr::core::rect<ind_int>(100, height - 35 - 20, width + 400,  height - 35 + 20)));
    _textPosition.insert(std::make_pair("range1", irr::core::rect<ind_int>(90, height - 80 - 20, width + 400,  height - 80 + 20)));
    _textPosition.insert(std::make_pair("bombNumber1", irr::core::rect<ind_int>(80, height - 125 - 20, width + 400,  height - 125 + 20 )));

    _textPosition.insert(std::make_pair("username2", irr::core::rect<ind_int>(180, 225 - 20, width + 400, 225 + 20)));
    _textPosition.insert(std::make_pair("speed2", irr::core::rect<ind_int>(100, 220 - 20, width + 400, 220 + 20)));
    _textPosition.insert(std::make_pair("range2", irr::core::rect<ind_int>(90, 175 - 20, width + 400, 175 + 20)));
    _textPosition.insert(std::make_pair("bombNumber2", irr::core::rect<ind_int>(80, 130 - 20, width + 400, 130 + 20)));

    _textPosition.insert(std::make_pair("username3", irr::core::rect<ind_int>(width - bgHUD->getSize().Width + 30, 225 - 20, width + 400, 225 + 20)));
    _textPosition.insert(std::make_pair("speed3", irr::core::rect<ind_int>(width - 110, 220 - 20, width + 400, 220 + 20)));
    _textPosition.insert(std::make_pair("range3", irr::core::rect<ind_int>(width - 100, 175 - 20, width + 400, 175 + 20)));
    _textPosition.insert(std::make_pair("bombNumber3", irr::core::rect<ind_int>(width - 90, 130 - 20, width + 400, 130 + 20)));

    _textPosition.insert(std::make_pair("username4", irr::core::rect<ind_int>(width - bgHUD->getSize().Width + 30, height - 30 - 20, width + 400, height - 30 + 20)));
    _textPosition.insert(std::make_pair("speed4", irr::core::rect<ind_int>(width - 110, height - 30 - 20, width + 400, height - 30 + 20)));
    _textPosition.insert(std::make_pair("range4", irr::core::rect<ind_int>(width - 100, height - 75 - 20, width + 400, height - 75 + 20)));
    _textPosition.insert(std::make_pair("bombNumber4", irr::core::rect<ind_int>(width - 90, height - 120 - 20, width + 400, height - 120 + 20)));

    _hudPosition.insert(std::make_pair("hud1", irr::core::position2d<int>(0, _saveDevice->getVideoDriver()->getScreenSize().Height - bgHUD->getSize().Height)));
    _hudPosition.insert(std::make_pair("hud2", irr::core::position2d<int>(0, 0)));
    _hudPosition.insert(std::make_pair("hud3", irr::core::position2d<int>(_saveDevice->getVideoDriver()->getScreenSize().Width - bgHUD->getSize().Width, 0)));
    _hudPosition.insert(std::make_pair("hud4", irr::core::position2d<int>(_saveDevice->getVideoDriver()->getScreenSize().Width - bgHUD->getSize().Width, _saveDevice->getVideoDriver()->getScreenSize().Height - bgHUD->getSize().Height)));
}

void ind::GameUI::initButtons()
{
    auto height = _saveDevice->getVideoDriver()->getScreenSize().Height;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;
    auto bgButtonPause = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgButtonPause",
                                                                           "bgButtonPause background not found");
    auto bgButtonHome = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgButtonHome",
                                                                          "bgButtonHome background not found");
    auto bgPause = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgPause",
                                                                     "bgPause background not found");
    auto bgButtonExit = ind::Menu::findWithExcept<irr::video::ITexture *>(_mapTextures, "bgButtonExit",
                                                                          "bgButtonExit background not found");
    /* init buttons*/
    _mapButtons.insert(std::make_pair("bgPause", _guiScene->addButton(
            irr::core::rect<ind_int>(0, 0, 1920,1080), nullptr, GUI_ID_NULL,L"")));
    _mapButtons.insert(std::make_pair("bgButtonPause", _guiScene->addButton(
            irr::core::rect<ind_int>(width / 2 - bgButtonPause->getSize().Width / 2 + 10, 0, width / 2 + bgButtonPause->getSize().Width / 2 + 10,bgButtonPause->getSize().Height), nullptr, GUI_ID_NULL,L"")));

    _mapButtons.insert(std::make_pair("buttonHome", _guiScene->addButton(
            irr::core::rect<ind_int>(width / 2 - bgButtonPause->getSize().Width,
                                     height / 2 - bgButtonHome->getSize().Height / 2,
                                     width / 2 + bgButtonPause->getSize().Width / 2,
                                     height / 2  + bgButtonHome->getSize().Height / 2 + 40 ), nullptr, GUI_ID_RUN_PRINCIPAL,L"")));

    _mapButtons.insert(std::make_pair("buttonExit", _guiScene->addButton(
            irr::core::rect<ind_int>(width / 2,
                                     height / 2 - bgButtonHome->getSize().Height / 2,
                                     width / 2 + bgButtonPause->getSize().Width / 2,
                                     height / 2  + bgButtonHome->getSize().Height / 2 + 40 ), nullptr, GUI_ID_QUIT_BUTTON,L"")));

    /* find Buttons */
    auto bgPauseButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "bgPause",
                                                                           "bgPause button not found");
    auto signPause = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "bgButtonPause",
                                                                       "bgButtonPause button not found");
    auto homeButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonHome",
                                                                        "buttonHome button not found");
    auto exitButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonExit",
                                                                        "buttonExit button not found");
    /* play with these buttons */
    bgPauseButton->setImage(bgPause);
    bgPauseButton->setVisible(false);
    bgPauseButton->setDrawBorder(false);
    bgPauseButton->setEnabled(false);
    bgPauseButton->setUseAlphaChannel(true);

    signPause->setImage(bgButtonPause);
    signPause->setVisible(false);
    signPause->setDrawBorder(false);
    signPause->setEnabled(false);
    signPause->setUseAlphaChannel(true);

    homeButton->setImage(bgButtonHome);
    homeButton->setVisible(false);
    homeButton->setDrawBorder(false);
    homeButton->setUseAlphaChannel(true);

    exitButton->setImage(bgButtonExit);
    exitButton->setVisible(false);
    exitButton->setDrawBorder(false);
    exitButton->setUseAlphaChannel(true);
}

void ind::GameUI::initTexts()
{
    auto height = _saveDevice->getVideoDriver()->getScreenSize().Height;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;
    auto homeButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonHome",
                                                                        "buttonHome was not found");
    /* INIT TEXTS */
    _mapTexts.insert(std::make_pair("volumeLabel",
                                    _guiScene->addStaticText(L"SONG VOLUME:",
                                                             irr::core::rect<ind_int>(width / 2 - 350,
                                                                                      height / 2 + homeButton->getRelativePosition().getHeight() - 100,
                                                                                      width / 2 + 350,
                                                                                      height / 2 +  homeButton->getRelativePosition().getHeight() - 100 + 100),
                                                             false)));
    _mapTexts.insert(std::make_pair("pause/gameOver",
                                    _guiScene->addStaticText(L"PAUSE",
                                                             irr::core::rect<ind_int>(width / 2 - 150,
                                                                                      height / 2 - homeButton->getRelativePosition().getHeight() + 100,
                                                                                      width / 2 + 150,
                                                                                      height / 2 -  homeButton->getRelativePosition().getHeight() + 200),
                                                             false)));
    _mapTexts.insert(std::make_pair("scorePlayerEndGame",
                                    _guiScene->addStaticText(L"",
                                                             irr::core::rect<ind_int>(width / 2 - 150,
                                                                                      height / 2 + homeButton->getRelativePosition().getHeight() - 100,
                                                                                      width / 2 + 500,
                                                                                      height / 2 +  homeButton->getRelativePosition().getHeight() - 100 + 100),
                                                             false)));
    auto textVolume = _mapTexts.find("volumeLabel");
    auto pauseGameOverText = _mapTexts.find("pause/gameOver");
    auto scorePlayerTextEndGame = _mapTexts.find("scorePlayerEndGame");

    textVolume->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
    textVolume->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    textVolume->second->setVisible(false);

    pauseGameOverText->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
    pauseGameOverText->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    pauseGameOverText->second->setVisible(false);

    scorePlayerTextEndGame->second->setOverrideFont(this->_guiScene->getFont(std::string(path + "/Assets/fonts/Splatch.png").c_str()));
    scorePlayerTextEndGame->second->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
    scorePlayerTextEndGame->second->setVisible(false);
}

void ind::GameUI::initScrollVolume()
{
    auto height = _saveDevice->getVideoDriver()->getScreenSize().Height;
    unsigned int width = _saveDevice->getVideoDriver()->getScreenSize().Width;
    auto homeButton = ind::Menu::findWithExcept<irr::gui::IGUIButton *>(_mapButtons, "buttonHome",
                                                                        "buttonHome was not found");
    /* Init Extra's */
    _mapExtra.insert<irr::gui::IGUIScrollBar *>("scrollbar", _guiScene->addScrollBar(true,
                                                                                     irr::core::rect<ind_int>(
                                                                                             width / 2 - 350,
                                                                                             height / 2 + homeButton->getRelativePosition().getHeight() - 20,
                                                                                             width / 2 + 350,
                                                                                             height / 2 +  homeButton->getRelativePosition().getHeight() - 20 + 35),
                                                                                     nullptr,
                                                                                     GUI_ID_VOLUME_SCROLL_BAR));
    /* Custom Extra's */
    auto scrollBar = _mapExtra.find<irr::gui::IGUIScrollBar *>("scrollbar");

    if (!scrollBar)
        EXCEPTION(std::runtime_error, "scrollbar was null");

    scrollBar->setMax(100);
    scrollBar->setPos(this->_gameScene->getEngineSound()->getVolumeOfASong("gameMusic"));
    scrollBar->setVisible(false);
}

std::shared_ptr<ind::Timer> ind::GameUI::getTimer(void) const
{
    return _timer;
}
