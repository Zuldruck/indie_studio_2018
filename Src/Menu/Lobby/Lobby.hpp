/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_LOBBY_H
#define BOMBERMAN_LOBBY_H

#include "Object.hpp"
#include "Includes.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include "Menu.hpp"

namespace ind {

    enum {
        GUI_ID_LOBBY_PREV,
        GUI_ID_LOBBY_NEXT,
        GUI_ID_LOBBY_MODE_PLAYER,
        GUI_ID_LOBBY_SKIN_BLUE,
        GUI_ID_LOBBY_SKIN_WHITE,
        GUI_ID_LOBBY_SKIN_BLACK,
        GUI_ID_LOBBY_SKIN_YELLOW,
        GUI_ID_LOBBY_SKIN_RED,
    };

    class EventReceiverLobby : public irr::IEventReceiver {
    public:
        EventReceiverLobby(irr::IrrlichtDevice *device);

        virtual ~EventReceiverLobby() = default;

        /**
         * @brief onEvent of the event Receivent
         * @param event event of the user.
         * @return true or false if the user event are detected.
         */
        virtual bool OnEvent(const irr::SEvent &event);

        std::string getBtnClick() { return this->_btnClick;};
        void setBtnClick(std::string btnClick) { this->_btnClick = btnClick;};

    private:
        irr::IrrlichtDevice *_saveDevice;
        std::string _btnClick;
    };

    class Lobby : public IMenu {

    public:
        virtual ~Lobby();

        Lobby(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver,
                irr::scene::ICameraSceneNode *camera, std::vector<std::shared_ptr<BombermanLobby>> vectBomberman);

        /**
         * @brief Draw GUI of this scene?
         */
        void drawGUi(float delta) override;

        /**
         * @brief Test if this menu is _active.
         * @return return true if the menu is _active, false otherwise.
         */
        bool isActive() const override;

        /**
         * @brief set the menu to _active or false.
         * @param _active
         */
        void setActive(bool _active) override;

        /**
         * @brief create all the GUI that this menu needed.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createGUI(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all imagines for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createImages(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all buttons for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createButtons(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all texts for this menu.
         * @param device device of the current window.
         * @param driver driver of the current window.
         */
        void createTexts(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief create all extra guy for this menu.
         * @param device drive of the current window.
         * @param driver driver of te current window.
         */
        void createExtra(irr::IrrlichtDevice *device, irr::video::IVideoDriver *driver) override;

        /**
         * @brief clean all map of this menu.
         */
        void cleanScope() override;

        /**
         * @brief update all gui things(button hover..)
         */
        void updateGUI(float delta) override;

        std::string getUsername() override;

        /**
         * @brief Movement Camera Menu to Lobby
         */
        void setMovementCameraMenuToLobby(float delta);

        /**
         * @brief Get position of the camera 0 1 2 3
         */
        void getPositionCamera();

        /**
         * @brief Get the bomberman's index in front of the camera
         * @return index
         */
        int getBomermanView();

        /**
         * @brief Reset caméra on menu
         */
        void setMovementCameraMenu(float delta);

        /**
         * @brief Camera movement on the prev bomberman
         */
        void setMovementCameraPrev(float delta);

        /**
         * @brief Camera movement on the next bomberman
         */
        void setMovementCameraNext(float delta);

        /**
        * @brief Set if the Bomberman is a Player or an IA
        */
        void setModePlayer(float delta);

        /**
        * @brief update name Player GUI
        */
        void setPlayerNameText(int idx);

        /**
        * @brief set blue bomberman skin
        */
        void setPlayerSkinBlue(float delta);

        /**
        * @brief set default bomberman skin
        */
        void setPlayerSkinWhite(float delta);

        /**
        * @brief set black bomberman skin
        */
        void setPlayerSkinBlack(float delta);

        /**
        * @brief set yellow bomberman skin
        */
        void setPlayerSkinYellow(float delta);

        /**
        * @brief set Jordan bomberman skin
        */
        void setPlayerSkinRed(float delta);

    private:

        irr::scene::ISceneManager *_lobbySceneManager;
        irr::gui::IGUIEnvironment *_guiScene;
        EventReceiverLobby _receiverLobby;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;
        irr::scene::ICameraSceneNode *_lobbyCamera;

        boost::unordered_map<std::string, irr::gui::IGUIButton *> _mapButtons;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *> _mapTexts;
        boost::unordered_map<std::string, irr::gui::IGUIImage *> _mapImages;
        boost::unordered_map<std::string, irr::video::ITexture *> _mapTextures;

        float _positionCamera;
        std::map<std::string, void (Lobby::*)(float)> _mapBtnAction;
        bool _prevIsActive;
        bool _nextIsActive;
        bool _lobbyIsActive;

        std::vector<std::shared_ptr<BombermanLobby>> _vectBomberman;

        std::string path;
        bool _active;
        bool _hoverBack;
        bool _hoverPlay;
        bool _hoverPrev;
        bool _hoverNext;
        bool _hoverChooseType;

    protected:
    };
}


#endif //BOMBERMAN_credits_H
