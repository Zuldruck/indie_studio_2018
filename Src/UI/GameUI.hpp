/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/


#ifndef BOMBERMAN_GAMEUI_HPP
#define BOMBERMAN_GAMEUI_HPP

#include "Includes.hpp"
#include "Core.hpp"
#include "GameScene.hpp"
#include "Timer.hpp"

namespace ind {

    class GameScene;

    /**
     * @brief GAMEUI is the class that create all HUD and bonuses of each players.
     */
    class GameUI
    {
    public:
        virtual ~GameUI() = default;
        GameUI() = default;
        GameUI(GameScene *gameScene);

        /**
         * @brief create all gui that a HUD player need.
         * @param position in Which corner of your window you want to display.
         */
        void createStyleUI(unsigned int position);

        /**
         * @brief create all bonuses with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createPowerUPUI(unsigned int position);

        /**
         * @brief create username with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createUsername(unsigned int position);

        /**
         * @brief create level with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createLevel(unsigned int position);

        /**
         * @brief create score with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createScore();

        /**
         * @brief create timer with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createTimer(unsigned int endTime);

        /**
         * @brief create speed bonuses with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createSpeed(unsigned int position);

        /**
         * @brief create bomb range with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createBombRange(unsigned int position);

        /**
         * @brief create bomb number with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createBombeNumber(unsigned int position);

        /**
         * @brief create HUD with a specific position.
         * @param position in Which corner of your window you want to display.
         */
        void createHUD(unsigned int position);

        /**
         * @brief init all textures
         */
        void initTextures();

        /**
         * @brief init in a map the position of all gui objects
         */
        void initPositionsGUI();

        /**
         * @brief init all buttons
         */
        void initButtons();

        /**
         * @brief init texts in a map the position of all gui objects
         */
        void initTexts();

        /**
         * @brief init scroll volume
         */
        void initScrollVolume();

        /**
         * @brief Pause and gameOver UI
         */
        void pauseAndGameOverUI(void);

        /**
         * @brief check if the timer is finisehd or not.
         * @return true if finished false otherwise.
         */
        bool timerIsFinished();

        /**
         * @brief update GUI.
         * @return true if timer is finished false otherwise.
         */
        bool update();

        /**
         * @brief update all texts of the game.
         * @return /!\
         */
        bool updateTexts();

        /**
         * @brief convert a string in Wchar_t
         * @param value value of string that you want to convert.
         * @return return a wstring which contains a wchar_t
         */
        static std::wstring convertStringToWchar(std::string value);

        /**
         * @brief Give the correct position for the HUD depending on the specific position?
         * @param key string of the position that you searched.
         * @param position position (1,2,3,4) depending on where you want to display it (1 bottom left corner and so on).
         * @return a rect of position.
         */
        inline irr::core::rect<ind_int>textConvertPositionIntoRect(const std::string& key, unsigned int position);
        inline irr::core::vector2d<int>hudConvertPositionInto2DPos(const std::string& key, unsigned int position);

        /**
         * @brief get the shared ptr of a timer.
         * @return shared ptr of the timer.
         */
        std::shared_ptr<Timer> getTimer() const;

        /**
         * @brief clean the content of all maps.
         */
        void cleanScope();

    private:
        bool _paused = false;
        int _lastSecond = 0;
        GameScene *_gameScene;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;

        boost::unordered_map<std::string, irr::gui::IGUIButton *> _mapButtons;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *> _mapTexts;
        boost::unordered_map<std::string, irr::gui::IGUIImage *> _mapImages;
        boost::unordered_map<std::string, irr::video::ITexture* > _mapTextures;
        boost::unordered_map<std::string, irr::core::rect<ind::ind_int>> _textPosition;
        boost::unordered_map<std::string, irr::core::vector2d<int>> _hudPosition;
        MapAnyTypes _mapExtra;

        std::shared_ptr<Timer> _timer;
        irr::gui::IGUIEnvironment* _guiScene;
        std::string path;
        unsigned int _nbPlayers;

    };

}



#endif //BOMBERMAN_GAMEUI_HPP
