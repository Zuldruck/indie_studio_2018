/*
** EPITECH PROJECT, 2019
** tek2
** File description:
** Undefined
*/

#ifndef BOMBERMAN_CONTROL_H
#define BOMBERMAN_CONTROL_H

#include "Menu.hpp"

namespace ind {

    /**
     * @brief Class which contains the key ingame.
     */
    class ControlKey : public IMenu {

    public:
        virtual ~ControlKey();

        ControlKey(Core &core, irr::IrrlichtDevice * device, irr::video::IVideoDriver * driver);

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

        /**
         * @brief override of getUsername. Useless for this class.
         * @return return the username in a string
         */
        std::string getUsername() override;


    private:

        irr::scene::ISceneManager *_controlKeySceneManager;
        irr::gui::IGUIEnvironment *_guiScene;
        EventReceiverMenu _receiver;
        irr::IrrlichtDevice *_saveDevice;
        irr::video::IVideoDriver *_saveDriver;

        boost::unordered_map<std::string, irr::gui::IGUIButton *> _mapButtons;
        boost::unordered_map<std::string, irr::gui::IGUIStaticText *> _mapTexts;
        boost::unordered_map<std::string, irr::gui::IGUIImage *> _mapImages;
        boost::unordered_map<std::string, irr::video::ITexture* > _mapTextures;
        boost::unordered_map<std::string, irr::gui::IGUIEditBox *> _mapKey;
        Core &_core;

        std::string path;
        bool _active;
        bool _hoverBack;

    protected:
    };
}

#endif //BOMBERMAN_PLAYMENU_H